#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <dirent.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"  // Assume graph.h and graph.c are available, compiled together

// Constants
#define OWNER_OFFSET 8  // Byte offset of __owner in pthread_mutex_t on x86_64 glibc
#define LIBPTHREAD_PATH "/lib/x86_64-linux-gnu/libpthread.so.0"  // Adjust if needed
#define MAX_TEMP_BP 1024  // Max simultaneous calls

// Structures
struct thread_state {
    pid_t tid;
    graph_node_t *wait_node;      // Node in wait_graph
    graph_node_t *held_head;      // Linked list of held dep nodes (mutex nodes)
    struct thread_state *next;
};

struct temp_bp {
    unsigned long addr;
    long orig_word;
    pid_t tid;                    // To associate with thread
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
    ts = malloc(sizeof(struct thread_state));
    ts->tid = tid;
    ts->wait_node = graph_find_or_create_node(wait_graph, (void *)(uintptr_t)tid);
    ts->held_head = NULL;
    ts->next = threads_head;
    threads_head = ts;
    return ts;
}

// Helper: Add held dep node (mutex node)
void add_held(struct thread_state *ts, graph_node_t *mutex_node) {
    mutex_node->next = ts->held_head;
    ts->held_head = mutex_node;
}

// Helper: Remove held dep node (find and remove)
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

// Helper: Find temp_bp by addr
struct temp_bp *find_temp_bp(unsigned long addr) {
    struct temp_bp *bp = temp_bps_head;
    while (bp) {
        if (bp->addr == addr) return bp;
        bp = bp->next;
    }
    return NULL;
}

// Helper: Remove and free temp_bp
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

// Helper: Read owner from mutex addr in process
pid_t read_owner(pid_t tid, unsigned long mutex) {
    long word = ptrace(PTRACE_PEEKDATA, tid, mutex + OWNER_OFFSET, NULL);
    if (word == -1) {
        perror("peek owner");
        return 0;
    }
    return (pid_t)word;  // __owner is int, but tid positive
}

// Helper: Find lib base from /proc/<pid>/maps
unsigned long find_lib_base(int pid, const char *libname) {
    char maps_path[64];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);
    FILE *f = fopen(maps_path, "r");
    if (!f) {
        perror("open maps");
        exit(1);
    }
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

// Helper: Get symbol offset from ELF file
unsigned long get_symbol_offset(const char *libpath, const char *symbol_name) {
    int fd = open(libpath, O_RDONLY);
    if (fd < 0) {
        perror("open lib");
        exit(1);
    }
    Elf64_Ehdr ehdr;
    read(fd, &ehdr, sizeof(ehdr));
    Elf64_Shdr *shdrs = malloc(ehdr.e_shentsize * ehdr.e_shnum);
    lseek(fd, ehdr.e_shoff, SEEK_SET);
    read(fd, shdrs, ehdr.e_shentsize * ehdr.e_shnum);

    Elf64_Shdr dynsym_shdr = {0}, dynstr_shdr = {0};
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (shdrs[i].sh_type == SHT_DYNSYM) dynsym_shdr = shdrs[i];
        if (shdrs[i].sh_type == SHT_STRTAB && strcmp("", "") == 0) {}  // Find .dynstr by link to dynsym
        if (shdrs[i].sh_type == SHT_STRTAB && shdrs[i].sh_link == 0 && shdrs[i].sh_flags & SHF_ALLOC) dynstr_shdr = shdrs[i];  // Approx
    }

    if (dynsym_shdr.sh_size == 0 || dynstr_shdr.sh_size == 0) {
        fprintf(stderr, "No dynsym or dynstr\n");
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

// Helper: Attach to all threads
void attach_all_threads(int pid) {
    char task_path[64];
    snprintf(task_path, sizeof(task_path), "/proc/%d/task", pid);
    DIR *dir = opendir(task_path);
    if (!dir) {
        perror("open task");
        exit(1);
    }
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_DIR && isdigit(ent->d_name[0])) {
            pid_t tid = atoi(ent->d_name);
            if (ptrace(PTRACE_ATTACH, tid, NULL, NULL) < 0) {
                perror("attach tid");
            }
        }
    }
    closedir(dir);
}

// Helper: Detach all threads (similar, but not implemented here for brevity)
void detach_all_threads(int pid) {
    // Similar to attach, but PTRACE_DETACH
    // Omitted for now, call on exit
}

// Helper: Insert breakpoint at addr in tid
void insert_bp(pid_t tid, unsigned long addr, long *orig_word) {
    *orig_word = ptrace(PTRACE_PEEKTEXT, tid, addr, NULL);
    long trap_word = (*orig_word & ~0xffL) | 0xccL;
    ptrace(PTRACE_POKETEXT, tid, addr, trap_word);
}

// Helper: Remove breakpoint
void remove_bp(pid_t tid, unsigned long addr, long orig_word) {
    ptrace(PTRACE_POKETEXT, tid, addr, orig_word);
}

// Helper: Handle single step after remove
void single_step_and_reinsert(pid_t tid, unsigned long addr, long orig_word) {
    remove_bp(tid, addr, orig_word);
    ptrace(PTRACE_SINGLESTEP, tid, NULL, NULL);
    int status;
    waitpid(tid, &status, 0);
    insert_bp(tid, addr, &orig_word);  // Reinsert
}

// Print func for tid
const char *print_tid(void *id) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "%ld", (long)(uintptr_t)id);
    return buf;
}

// Print func for mutex
const char *print_mutex(void *id) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "%p", id);
    return buf;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(1);
    }
    int pid = atoi(argv[1]);

    // Init graphs
    wait_graph = graph_create();
    dep_graph = graph_create();

    // Find addresses
    unsigned long base = find_lib_base(pid, "libpthread.so");
    if (base == 0) {
        fprintf(stderr, "Libpthread not found\n");
        exit(1);
    }
    unsigned long lock_offset = get_symbol_offset(LIBPTHREAD_PATH, "pthread_mutex_lock");
    unsigned long unlock_offset = get_symbol_offset(LIBPTHREAD_PATH, "pthread_mutex_unlock");
    lock_addr = base + lock_offset;
    unlock_addr = base + unlock_offset;

    // Attach to all threads
    attach_all_threads(pid);

    // Insert breakpoints in all threads (since code shared)
    // But since text is shared, inserting in one affects all, but to be safe, insert via one tid
    insert_bp(pid, lock_addr, &orig_lock_word);
    insert_bp(pid, unlock_addr, &orig_unlock_word);

    // Main loop
    while (1) {
        int status;
        pid_t tid = waitpid(-1, &status, 0);
        if (tid < 0) break;
        if (WIFEXITED(status)) continue;
        if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, tid, NULL, &regs);
            unsigned long rip = regs.rip - 1;

            struct thread_state *ts = get_or_create_thread_state(tid);

            if (rip == lock_addr) {
                // Lock entry
                unsigned long mutex = regs.rdi;
                pid_t owner = read_owner(tid, mutex);

                graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);

                // Check potential deadlock (order violation)
                graph_node_t *held = ts->held_head;
                while (held) {
                    if (graph_would_create_cycle(dep_graph, held, mutex_node)) {
                        fprintf(stderr, "Potential deadlock detected: Thread %ld acquiring %p while holding %p\n",
                                (long)tid, (void *)mutex, graph_node_get_id(held));
                        graph_print(dep_graph, print_mutex);
                    }
                    held = held->next;
                }

                // Get return addr from stack
                long ret_addr_word = ptrace(PTRACE_PEEKDATA, tid, regs.rsp, NULL);
                unsigned long ret_addr = (unsigned long)ret_addr_word;

                // Insert temp bp at return addr
                struct temp_bp *new_bp = malloc(sizeof(struct temp_bp));
                new_bp->addr = ret_addr;
                new_bp->tid = tid;
                new_bp->mutex = mutex;
                new_bp->next = temp_bps_head;
                long dummy_orig;  // Will set when insert
                insert_bp(tid, ret_addr, &new_bp->orig_word);
                temp_bps_head = new_bp;

                // Handle wait if needed
                if (owner != 0 && owner != tid) {
                    graph_node_t *owner_node = graph_find_or_create_node(wait_graph, (void *)(uintptr_t)owner);
                    if (graph_would_create_cycle(wait_graph, ts->wait_node, owner_node)) {
                        fprintf(stderr, "Actual deadlock detected: Thread %ld waiting on %ld for %p\n",
                                (long)tid, (long)owner, (void *)mutex);
                        graph_print(wait_graph, print_tid);
                    } else {
                        graph_add_edge(wait_graph, ts->wait_node, owner_node);
                    }
                }

                // Proceed: single step and reinsert entry bp
                single_step_and_reinsert(tid, lock_addr, orig_lock_word);

            } else if (rip == unlock_addr) {
                // Unlock entry
                unsigned long mutex = regs.rdi;
                pid_t owner = read_owner(tid, mutex);
                if (owner != tid) {
                    fprintf(stderr, "Unlock by non-owner: %ld on %p owned by %ld\n", (long)tid, (void *)mutex, (long)owner);
                }

                graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);
                remove_held(ts, mutex_node);

                // Proceed
                single_step_and_reinsert(tid, unlock_addr, orig_unlock_word);

            } else {
                // Check if temp bp (return from lock)
                struct temp_bp *bp = find_temp_bp(rip);
                if (bp && bp->tid == tid) {
                    // Lock return: acquired
                    unsigned long mutex = bp->mutex;
                    graph_node_t *mutex_node = graph_find_or_create_node(dep_graph, (void *)mutex);

                    // Remove wait edge if any (find owner at time, but since acquired, clear outgoing from this thread? Better clear all outgoing
                    clear_outgoing(wait_graph, ts->wait_node);  // Since acquired, no longer waiting

                    // Add to held
                    add_held(ts, mutex_node);

                    // Update dep_graph: add edges from previous held to this
                    graph_node_t *prev = ts->held_head->next;  // Skip new
                    while (prev) {
                        graph_add_edge(dep_graph, prev, mutex_node);
                        prev = prev->next;
                    }

                    // Remove the temp bp
                    single_step_and_reinsert(tid, rip, bp->orig_word);  // rip is addr
                    remove_temp_bp(bp);

                } else {
                    // Unknown trap, continue
                    ptrace(PTRACE_CONT, tid, NULL, NULL);
                }
            }
        } else {
            ptrace(PTRACE_CONT, tid, NULL, NULL);
        }
    }

    // Cleanup
    detach_all_threads(pid);
    graph_destroy(wait_graph);
    graph_destroy(dep_graph);
    // Free lists...
    return 0;
}
