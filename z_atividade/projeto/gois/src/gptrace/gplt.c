#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "graph.h"  // From your repo, compiled together

// Constants
#define OWNER_OFFSET 8  // Byte offset of __owner in pthread_mutex_t (x86_64 glibc)
#define LIBPTHREAD_PATH "/lib/x86_64-linux-gnu/libpthread.so.0"  // Adjust if needed
#define MAX_THREADS 1024
#define MAX_TEMP_BP 1024  // Max simultaneous breakpoints
#define MAX_STACK_FRAMES 32  // Max frames to walk

// Structures
struct thread_state {
    pid_t tid;
    graph_node_t *wait_node;      // Node in wait_graph (thread)
    graph_node_t *held_head;      // Linked list of held dep nodes (mutexes)
    struct thread_state *next;
};

struct temp_bp {
    unsigned long addr;            // Breakpoint address
    long orig_word;               // Original instruction
    pid_t tid;                    // Thread that hit it
    unsigned long mutex;          // Mutex being acquired
    struct temp_bp *next;
};

// Globals
graph_t *wait_graph;
graph_t *dep_graph;
struct thread_state *threads_head = NULL;
struct temp_bp *temp_bps_head = NULL;
unsigned long lock_addr = 0;
unsigned long unlock_addr = 0;
long orig_lock_word = 0;
long orig_unlock_word = 0;

// Helper: Find or create thread_state
struct thread_state *get_or_create_thread_state(pid_t tid) {
    struct thread_state *ts = threads_head;
    while (ts) {
        if (ts->tid == tid) return ts;
        ts = ts->next;
    }
    ts = calloc(1, sizeof(struct thread_state));
    if (!ts) { perror("calloc thread_state"); exit(1); }
    ts->tid = tid;
    ts->wait_node = graph_find_or_create_node(wait_graph, (void *)(uintptr_t)tid);
    if (!ts->wait_node) { fprintf(stderr, "Failed to create wait node\n"); exit(1); }
    ts->next = threads_head;
    threads_head = ts;
    return ts;
}

// Helper: Add held mutex node
void add_held(struct thread_state *ts, graph_node_t *mutex_node) {
    mutex_node->next = ts->held_head;
    ts->held_head = mutex_node;
}

// Helper: Remove held mutex node
void remove_held(struct thread_state *ts, graph_node_t *mutex_node) {
    graph_node_t **curr = &ts->held_head;
    while (*curr) {
        if (*curr == mutex_node) {
            *curr = (*curr)->next;
            return;
        }
        curr = &(*curr)->next;
    }
}

// Helper: Find temp breakpoint
struct temp_bp *find_temp_bp(unsigned long addr, pid_t tid) {
    struct temp_bp *bp = temp_bps_head;
    while (bp) {
        if (bp->addr == addr && bp->tid == tid) return bp;
        bp = bp->next;
    }
    return NULL;
}

// Helper: Add temp breakpoint
struct temp_bp *add_temp_bp(pid_t tid, unsigned long addr, unsigned long mutex) {
    struct temp_bp *bp = calloc(1, sizeof(struct temp_bp));
    if (!bp) { perror("calloc temp_bp"); exit(1); }
    bp->addr = addr;
    bp->tid = tid;
    bp->mutex = mutex;
    bp->next = temp_bps_head;
    temp_bps_head = bp;
    return bp;
}

// Helper: Remove temp breakpoint
void remove_temp_bp(struct temp_bp *bp) {
    struct temp_bp **curr = &temp_bps_head;
    while (*curr) {
        if (*curr == bp) {
            *curr = (*curr)->next;
            free(bp);
            return;
        }
        curr = &(*curr)->next;
    }
}

// Helper: Clear outgoing wait edges
void clear_outgoing_wait_edges(graph_t *graph, graph_node_t *from) {
    graph_edge_t *prev = NULL;
    graph_edge_t *edge = graph->edges;
    while (edge) {
        if (edge->from == from) {
            graph_edge_t *tmp = edge;
            edge = edge->next;
            if (prev) prev->next = edge;
            else graph->edges = edge;
            free(tmp);
            graph->edge_count--;
        } else {
            prev = edge;
            edge = edge->next;
        }
    }
}

// Helper: Read memory from tracee
long read_mem(pid_t tid, unsigned long addr) {
    errno = 0;
    long word = ptrace(PTRACE_PEEKDATA, tid, addr, NULL);
    if (errno != 0) {
        perror("peekdata");
        return -1;
    }
    return word;
}

// Helper: Read owner from mutex
pid_t read_owner(pid_t tid, unsigned long mutex) {
    long word = read_mem(tid, mutex + OWNER_OFFSET);
    return word == -1 ? 0 : (pid_t)word;
}

// Helper: Find lib base in /proc/<pid>/maps
unsigned long find_lib_base(int pid, const char *libname) {
    char maps_path[64];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);
    FILE *f = fopen(maps_path, "r");
    if (!f) { perror("open maps"); exit(1); }
    char line[256];
    unsigned long base = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, libname)) {
            sscanf(line, "%lx", &base);
            break;
        }
    }
    fclose(f);
    return base;
}

// Helper: Get symbol offset from ELF
unsigned long get_symbol_offset(const char *libpath, const char *symbol_name) {
    int fd = open(libpath, O_RDONLY);
    if (fd < 0) { perror("open lib"); exit(1); }
    Elf64_Ehdr ehdr;
    read(fd, &ehdr, sizeof(ehdr));
    Elf64_Shdr *shdrs = malloc(ehdr.e_shentsize * ehdr.e_shnum);
    lseek(fd, ehdr.e_shoff, SEEK_SET);
    read(fd, shdrs, ehdr.e_shentsize * ehdr.e_shnum);

    Elf64_Shdr dynsym_shdr = {0}, dynstr_shdr = {0};
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (shdrs[i].sh_type == SHT_DYNSYM) dynsym_shdr = shdrs[i];
        if (shdrs[i].sh_type == SHT_STRTAB && shdrs[i].sh_flags & SHF_ALLOC) dynstr_shdr = shdrs[i];
    }

    if (dynsym_shdr.sh_size == 0 || dynstr_shdr.sh_size == 0) {
        fprintf(stderr, "No dynsym or dynstr\n");
        free(shdrs);
        close(fd);
        exit(1);
    }

    Elf64_Sym *syms = malloc(dynsym_shdr.sh_size);
    lseek(fd, dynsym_shdr.sh_offset, SEEK_SET);
    read(fd, syms, dynsym_shdr.sh_size);

    char *strtab = malloc(dynstr_shdr.sh_size);
    lseek(fd, dynstr_shdr.sh_offset, SEEK_SET);
    read(fd, strtab, dynstr_shdr.sh_size);

    unsigned long offset = 0;
    int nsyms = dynsym_shdr.sh_size / sizeof(Elf64_Sym);
    for (int i = 0; i < nsyms; i++) {
        if (strcmp(strtab + syms[i].st_name, symbol_name) == 0) {
            offset = syms[i].st_value;
            break;
        }
    }

    free(syms);
    free(strtab);
    free(shdrs);
    close(fd);
    return offset;
}

// Helper: Insert breakpoint
void insert_bp(pid_t tid, unsigned long addr, long *orig_word) {
    *orig_word = ptrace(PTRACE_PEEKTEXT, tid, addr, NULL);
    long trap_word = (*orig_word & ~0xffL) | 0xccL;
    ptrace(PTRACE_POKETEXT, tid, addr, trap_word);
}

// Helper: Remove breakpoint
void remove_bp(pid_t tid, unsigned long addr, long orig_word) {
    ptrace(PTRACE_POKETEXT, tid, addr, orig_word);
}

// Helper: Single step and reinsert
void single_step_and_reinsert(pid_t tid, unsigned long addr, long orig_word) {
    remove_bp(tid, addr, orig_word);
    ptrace(PTRACE_SINGLESTEP, tid, NULL, NULL);
    int status;
    waitpid(tid, &status, 0);
    insert_bp(tid, addr, &orig_word);
}

// Helper: Perform backtrace to verify mutex call
bool is_mutex_lock_call(pid_t tid, unsigned long rip, unsigned long *mutex_arg) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, tid, NULL, ®s);

    // Inline assembly to read rbp safely
    unsigned long rbp;
    asm volatile("mov %%rbp, %0" : "=r"(rbp));

    unsigned long rsp = regs.rsp;
    unsigned long frame_ptr = regs.rbp;
    int depth = 0;
    bool found = false;

    // Walk stack
    while (depth < MAX_STACK_FRAMES && frame_ptr != 0) {
        // Read return address
        long ret_addr = read_mem(tid, frame_ptr + 8);
        if (ret_addr == -1) break;

        // Check if caller is in libpthread near lock_addr
        if (ret_addr >= lock_addr && ret_addr < lock_addr + 0x1000) {
            *mutex_arg = regs.rdi;  // First arg in x86_64
            found = true;
            break;
        }

        // Check instruction before call (callq is 5 bytes, look for mov to rdi)
        unsigned char instr[16];
        for (int i = 0; i < 16; i++) {
            long word = read_mem(tid, ret_addr - 16 + i);
            if (word == -1) break;
            instr[i] = (unsigned char)word;
        }
        // Look for "mov %reg, %rdi" or similar before call
        // Example: 48 89 ?? 48 89 f8 (mov %reg, %rdi; mov %rdi, %rax)
        if (instr[0] == 0x48 && instr[1] == 0x89 && (instr[2] & 0xc0) == 0xc0) {
            // Possible mutex setup
            *mutex_arg = regs.rdi;
            found = true;
            break;
        }

        // Move to next frame
        long next_frame = read_mem(tid, frame_ptr);
        if (next_frame == -1) break;
        frame_ptr = next_frame;
        depth++;
    }

    return found;
}

// Helper: Print graphs for debug
const char *print_tid(void *id) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "%ld", (long)(uintptr_t)id);
    return buf;
}

const char *print_mutex(void *id) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "%p", id);
    return buf;
}

// Main
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(1);
    }
    int pid = atoi(argv[1]);

    // Initialize graphs
    wait_graph = graph_create();
    dep_graph = graph_create();
    if (!wait_graph || !dep_graph) {
        fprintf(stderr, "Failed to create graphs\n");
        exit(1);
    }

    // Find libpthread addresses
    unsigned long base = find_lib_base(pid, "libpthread.so");
    if (base == 0) {
        fprintf(stderr, "Warning: libpthread not found, relying on backtrace\n");
    } else {
        unsigned long lock_offset = get_symbol_offset(LIBPTHREAD_PATH, "pthread_mutex_lock");
        unsigned long unlock_offset = get_symbol_offset(LIBPTHREAD_PATH, "pthread_mutex_unlock");
        lock_addr = base + lock_offset;
        unlock_addr = base + unlock_offset;
    }

    // Attach to all threads
    char task_path[64];
    snprintf(task_path, sizeof(task_path), "/proc/%d/task", pid);
    DIR *dir = opendir(task_path);
    if (!dir) { perror("open task"); exit(1); }
    struct dirent *ent;
    while ((ent = readdir(dir))) {
        if (ent->d_type == DT_DIR && isdigit(ent->d_name[0])) {
            pid_t tid = atoi(ent->d_name);
            if (ptrace(PTRACE_ATTACH, tid, NULL, NULL) < 0) {
                perror("attach tid");
            } else {
                waitpid(tid, NULL, 0);  // Wait for stop
            }
        }
    }
    closedir(dir);

    // Insert breakpoints if addresses known
    if (lock_addr && unlock_addr) {
        insert_bp(pid, lock_addr, &orig_lock_word);
        insert_bp(pid, unlock_addr, &orig_unlock_word);
    }

    // Main loop
    while (1) {
        int status;
        pid_t tid = waitpid(-1, &status, 0);
        if (tid < 0) break;
        if (WIFEXITED(status)) {
            // Remove thread state
            struct thread_state **ts = &threads_head;
            while (*ts) {
                if ((*ts)->tid == tid) {
                    struct thread_state *tmp = *ts;
                    *ts = (*ts)->next;
                    free(tmp);
                    break;
                }
                ts = &(*ts)->next;
            }
            continue;
        }
        if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, tid, NULL, ®s);
            unsigned long rip = regs.rip - 1;

            struct thread_state *ts = get_or_create_thread_state(tid);
            unsigned long mutex = 0;
            bool is_lock = false;

            // Check if at lock or unlock, or use backtrace
            if (rip == lock_addr) {
                is_lock = true;
                mutex = regs.rdi;
            } else if (rip == unlock_addr) {
                mutex = regs.rdi;
            } else {
                // Try backtrace to confirm mutex lock
                if (is_mutex_lock_call(tid, rip, &mutex)) {
                    is_lock = true;
                }
            }

            if (is_lock) {
                // Handle lock attempt
                pid_t owner = read_owner(tid, mutex);
                graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);

                // Check potential deadlock
                graph_node_t *held = ts->held_head;
                while (held) {
                    if (graph_would_create_cycle(dep_graph, held, mutex_node)) {
                        fprintf(stderr, "Potential deadlock: Thread %ld acquiring %p while holding %p\n",
                                (long)tid, (void *)mutex, graph_node_get_id(held));
                        graph_print(dep_graph, print_mutex);
                    }
                    held = held->next;
                }

                // Set temp breakpoint at return address
                long ret_addr = read_mem(tid, regs.rsp);
                if (ret_addr != -1) {
                    struct temp_bp *bp = add_temp_bp(tid, ret_addr, mutex);
                    insert_bp(tid, ret_addr, &bp->orig_word);
                }

                // Check actual deadlock if waiting
                if (owner != 0 && owner != tid) {
                    graph_node_t *owner_node = graph_find_or_create_node(wait_graph, (void *)(uintptr_t)owner);
                    if (graph_would_create_cycle(wait_graph, ts->wait_node, owner_node)) {
                        fprintf(stderr, "Actual deadlock: Thread %ld waiting on %ld for %p\n",
                                (long)tid, (long)owner, (void *)mutex);
                        graph_print(wait_graph, print_tid);
                    } else {
                        graph_add_edge(wait_graph, ts->wait_node, owner_node);
                    }
                }

                // Proceed
                if (rip == lock_addr) {
                    single_step_and_reinsert(tid, lock_addr, orig_lock_word);
                } else {
                    ptrace(PTRACE_CONT, tid, NULL, NULL);
                }

            } else if (rip == unlock_addr || (mutex && !is_lock)) {
                // Handle unlock
                pid_t owner = read_owner(tid, mutex);
                if (owner != tid) {
                    fprintf(stderr, "Unlock by non-owner: %ld on %p owned by %ld\n", (long)tid, (void *)mutex, (long)owner);
                }

                graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);
                remove_held(ts, mutex_node);

                if (rip == unlock_addr) {
                    single_step_and_reinsert(tid, unlock_addr, orig_unlock_word);
                } else {
                    ptrace(PTRACE_CONT, tid, NULL, NULL);
                }

            } else {
                // Check temp breakpoint (lock return)
                struct temp_bp *bp = find_temp_bp(rip, tid);
                if (bp) {
                    mutex = bp->mutex;
                    graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);

                    // Acquired: clear wait edges
                    clear_outgoing_wait_edges(wait_graph, ts->wait_node);

                    // Add to held
                    add_held(ts, mutex_node);

                    // Update dep_graph
                    graph_node_t *prev = ts->held_head->next;
                    while (prev) {
                        graph_add_edge(dep_graph, prev, mutex_node);
                        prev = prev->next;
                    }

                    // Remove temp bp
                    single_step_and_reinsert(tid, rip, bp->orig_word);
                    remove_temp_bp(bp);
                } else {
                    ptrace(PTRACE_CONT, tid, NULL, NULL);
                }
            }
        } else {
            ptrace(PTRACE_CONT, tid, NULL, NULL);
        }
    }

    // Cleanup
    dir = opendir(task_path);
    if (dir) {
        while ((ent = readdir(dir))) {
            if (ent->d_type == DT_DIR && isdigit(ent->d_name[0])) {
                pid_t tid = atoi(ent->d_name);
                ptrace(PTRACE_DETACH, tid, NULL, NULL);
            }
        }
        closedir(dir);
    }

    // Free resources
    struct thread_state *ts = threads_head;
    while (ts) {
        struct thread_state *tmp = ts;
        ts = ts->next;
        free(tmp);
    }
    struct temp_bp *bp = temp_bps_head;
    while (bp) {
        struct temp_bp *tmp = bp;
        bp = bp->next;
        free(tmp);
    }
    graph_destroy(wait_graph);
    graph_destroy(dep_graph);

    return 0;
}
