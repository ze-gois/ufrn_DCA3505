/**
 * @file backtrace.c
 * @brief Implementation of backtrace analysis for ptrace-based deadlock detection
 *
 * This file implements functions for capturing and analyzing stack traces
 * from threads in a traced process using ptrace, allowing for identification
 * of threads blocked in mutex operations.
 */

#include "backtrace.h"
#include "ptrace_attach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <elf.h>
#include <link.h>
#include <dlfcn.h>
#include <dirent.h>

// Optional libelf support - fallback to addr2line if not available
#ifdef HAVE_LIBELF
#include <libelf.h>
#include <gelf.h>
#define USE_LIBELF 1
#else
#define USE_LIBELF 0
#endif

// Print debugging information if enabled
#define DEBUG 1
#define debug_print(fmt, ...) \
    do { if (DEBUG) fprintf(stderr, "[BACKTRACE] " fmt, ##__VA_ARGS__); } while (0)

// Flag for using debug symbols
static bool use_debug_symbols = true;

// Path to the executable of the target process
static char executable_path[PATH_MAX] = {0};

// Structure to store symbol information
typedef struct {
    void* addr;                   // Symbol address
    unsigned long size;           // Symbol size
    char name[MAX_SYMBOL_LENGTH]; // Symbol name
    unsigned long offset;         // Offset from base address
    bool is_function;             // Whether this is a function symbol
} symbol_info_t;

#if USE_LIBELF
// Structure to store ELF file information
typedef struct {
    int fd;                       // File descriptor
    Elf* elf;                     // ELF handle
    GElf_Ehdr ehdr;              // ELF header
    Elf_Scn* symtab_scn;         // Symbol table section
    Elf_Scn* dynsym_scn;         // Dynamic symbol table section
    Elf_Data* symtab_data;       // Symbol table data
    Elf_Data* dynsym_data;       // Dynamic symbol table data
    size_t symtab_count;         // Number of symbols in symbol table
    size_t dynsym_count;         // Number of symbols in dynamic symbol table
    char* strtab;                // String table
    char* dynstr;                // Dynamic string table
    size_t strtab_size;          // String table size
    size_t dynstr_size;          // Dynamic string table size
    unsigned long base_addr;     // Base load address
} elf_info_t;

// Global ELF information cache
static elf_info_t* elf_cache = NULL;
static bool elf_initialized = false;
#endif

#if USE_LIBELF
/**
 * Initialize libelf
 */
static bool init_elf_library(void) {
    if (elf_initialized) {
        return true;
    }
    
    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        return false;
    }
    
    elf_initialized = true;
    return true;
}
#endif

#if USE_LIBELF
/**
 * Clean up ELF information
 */
static void cleanup_elf_info(elf_info_t* elf_info) {
    if (elf_info == NULL) return;
    
    if (elf_info->elf != NULL) {
        elf_end(elf_info->elf);
    }
    if (elf_info->fd >= 0) {
        close(elf_info->fd);
    }
    free(elf_info);
}
#endif

#if USE_LIBELF
/**
 * Load ELF file information
 */
static elf_info_t* load_elf_info(const char* filepath) {
    if (!init_elf_library()) {
        return NULL;
    }
    
    elf_info_t* elf_info = malloc(sizeof(elf_info_t));
    if (!elf_info) {
        return NULL;
    }
    
    memset(elf_info, 0, sizeof(elf_info_t));
    elf_info->fd = -1;
    
    // Open the file
    elf_info->fd = open(filepath, O_RDONLY);
    if (elf_info->fd < 0) {
        cleanup_elf_info(elf_info);
        return NULL;
    }
    
    // Initialize ELF
    elf_info->elf = elf_begin(elf_info->fd, ELF_C_READ, NULL);
    if (!elf_info->elf) {
        cleanup_elf_info(elf_info);
        return NULL;
    }
    
    // Check if it's an ELF file
    if (elf_kind(elf_info->elf) != ELF_K_ELF) {
        cleanup_elf_info(elf_info);
        return NULL;
    }
    
    // Get ELF header
    if (gelf_getehdr(elf_info->elf, &elf_info->ehdr) == NULL) {
        cleanup_elf_info(elf_info);
        return NULL;
    }
    
    // Find symbol tables
    Elf_Scn* scn = NULL;
    while ((scn = elf_nextscn(elf_info->elf, scn)) != NULL) {
        GElf_Shdr shdr;
        if (gelf_getshdr(scn, &shdr) == NULL) {
            continue;
        }
        
        if (shdr.sh_type == SHT_SYMTAB) {
            elf_info->symtab_scn = scn;
            elf_info->symtab_data = elf_getdata(scn, NULL);
            if (elf_info->symtab_data) {
                elf_info->symtab_count = shdr.sh_size / shdr.sh_entsize;
            }
        } else if (shdr.sh_type == SHT_DYNSYM) {
            elf_info->dynsym_scn = scn;
            elf_info->dynsym_data = elf_getdata(scn, NULL);
            if (elf_info->dynsym_data) {
                elf_info->dynsym_count = shdr.sh_size / shdr.sh_entsize;
            }
        }
    }
    
    return elf_info;
}
#endif

/**
 * Helper function to get the executable path for a process
 */
static bool get_process_executable(pid_t pid, char* path, size_t max_len) {
    char proc_exe[PATH_MAX];
    snprintf(proc_exe, sizeof(proc_exe), "/proc/%d/exe", pid);

    ssize_t len = readlink(proc_exe, path, max_len - 1);
    if (len < 0) {
        perror("readlink");
        return false;
    }

    path[len] = '\0';
    return true;
}

/**
 * Helper function to read a value from a register
 */
static unsigned long get_register_value(pid_t pid, int reg) {
    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1) {
        perror("ptrace getregs");
        return 0;
    }

    // Map register index to the appropriate register
    switch (reg) {
        case 0: return regs.rax;
        case 1: return regs.rbx;
        case 2: return regs.rcx;
        case 3: return regs.rdx;
        case 4: return regs.rsi;
        case 5: return regs.rdi;
        case 6: return regs.rbp;
        case 7: return regs.rsp;
        case 8: return regs.r8;
        case 9: return regs.r9;
        case 10: return regs.r10;
        case 11: return regs.r11;
        case 12: return regs.r12;
        case 13: return regs.r13;
        case 14: return regs.r14;
        case 15: return regs.r15;
        case 16: return regs.rip;
        default: return 0;
    }
}

#if USE_LIBELF
/**
 * Search for a symbol in the ELF symbol table
 */
static bool find_symbol_in_table(elf_info_t* elf_info __attribute__((unused)), void* addr, symbol_info_t* info,
                                 Elf_Data* symdata, size_t sym_count, const char* strtab) {
    if (!symdata || !strtab) {
        return false;
    }
    
    unsigned long target_addr = (unsigned long)addr;
    GElf_Sym best_sym;
    bool found = false;
    unsigned long best_distance = ULONG_MAX;
    
    for (size_t i = 0; i < sym_count; i++) {
        GElf_Sym sym;
        if (gelf_getsym(symdata, i, &sym) == NULL) {
            continue;
        }
        
        // Skip undefined symbols
        if (sym.st_shndx == SHN_UNDEF || sym.st_value == 0) {
            continue;
        }
        
        // Check if target address falls within this symbol's range
        unsigned long sym_start = sym.st_value;
        unsigned long sym_end = sym_start + sym.st_size;
        
        if (target_addr >= sym_start && (sym.st_size == 0 || target_addr < sym_end)) {
            // Exact match
            found = true;
            best_sym = sym;
            best_distance = target_addr - sym_start;
            break;
        } else if (target_addr >= sym_start && target_addr - sym_start < best_distance) {
            // Best approximate match so far
            found = true;
            best_sym = sym;
            best_distance = target_addr - sym_start;
        }
    }
    
    if (found) {
        const char* name = strtab + best_sym.st_name;
        if (name && strlen(name) > 0) {
            strncpy(info->name, name, MAX_SYMBOL_LENGTH - 1);
            info->name[MAX_SYMBOL_LENGTH - 1] = '\0';
            info->addr = (void*)best_sym.st_value;
            info->size = best_sym.st_size;
            info->offset = best_distance;
            info->is_function = (GELF_ST_TYPE(best_sym.st_info) == STT_FUNC);
            return true;
        }
    }
    
    return false;
}
#endif

/**
 * Helper function to find a symbol in the executable or shared libraries
 */
static bool find_symbol_info(void* addr, symbol_info_t* info) {
    if (!use_debug_symbols || executable_path[0] == '\0') {
        return false;
    }

    // Initialize info with defaults
    info->addr = addr;
    info->size = 0;
    info->offset = 0;
    info->is_function = false;
    snprintf(info->name, MAX_SYMBOL_LENGTH, "??");

#if USE_LIBELF
    // Load ELF information if not already cached
    if (elf_cache == NULL) {
        elf_cache = load_elf_info(executable_path);
        if (elf_cache == NULL) {
            debug_print("Failed to load ELF info for %s\n", executable_path);
        }
    }

    // Try to find symbol in symbol table first
    if (elf_cache && elf_cache->symtab_data && elf_cache->strtab) {
        if (find_symbol_in_table(elf_cache, addr, info, 
                                elf_cache->symtab_data, elf_cache->symtab_count, 
                                elf_cache->strtab)) {
            return true;
        }
    }

    // Try dynamic symbol table as fallback
    if (elf_cache && elf_cache->dynsym_data && elf_cache->dynstr) {
        if (find_symbol_in_table(elf_cache, addr, info, 
                                elf_cache->dynsym_data, elf_cache->dynsym_count, 
                                elf_cache->dynstr)) {
            return true;
        }
    }
#endif

    // Final fallback to addr2line
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "addr2line -e %s -f -s -p %p 2>/dev/null", executable_path, addr);

    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return false;
    }

    char line[MAX_SYMBOL_LENGTH];
    if (fgets(line, sizeof(line), pipe) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char* at_pos = strstr(line, " at ");
        if (at_pos) {
            *at_pos = '\0';
        }
        
        strncpy(info->name, line, MAX_SYMBOL_LENGTH - 1);
        info->name[MAX_SYMBOL_LENGTH - 1] = '\0';
    }

    pclose(pipe);
    return strlen(info->name) > 2;
}

/**
 * Helper function to unwind the stack using frame pointers
 */
static int unwind_stack_fp(pid_t pid, void** frames, int max_frames) {
    unsigned long rbp, rip, rsp;
    int frame_count = 0;

    // Get initial values of registers
    rbp = get_register_value(pid, 6);  // RBP
    rip = get_register_value(pid, 16); // RIP
    rsp = get_register_value(pid, 7);  // RSP

    if (rbp == 0 || rip == 0 || rsp == 0) {
        debug_print("Failed to get initial register values\n");
        return 0;
    }

    // Store the current instruction pointer as the first frame
    if (frame_count < max_frames) {
        frames[frame_count++] = (void*)rip;
    }

    // Walk the stack using frame pointers
    while (frame_count < max_frames && rbp != 0) {
        // The return address is stored at rbp+8
        unsigned long next_rip, next_rbp;
        if (!ptrace_read_memory(pid, rbp + 8, &next_rip, sizeof(next_rip)) ||
            !ptrace_read_memory(pid, rbp, &next_rbp, sizeof(next_rbp))) {
            break;
        }

        // Check for obviously invalid values
        if (next_rip == 0 || next_rbp <= rbp) {
            break;
        }

        frames[frame_count++] = (void*)next_rip;
        rbp = next_rbp;
    }

    return frame_count;
}

bool backtrace_init(void) {
#if USE_LIBELF
    if (!init_elf_library()) {
        debug_print("Failed to initialize ELF library\n");
        // Continue anyway, fallback methods will be used
    }
#endif
    return true;
}

void backtrace_cleanup(void) {
#if USE_LIBELF
    if (elf_cache != NULL) {
        cleanup_elf_info(elf_cache);
        elf_cache = NULL;
    }
#endif
}

bool backtrace_capture(pid_t pid, thread_backtrace_t* backtrace) {
    if (backtrace == NULL) {
        return false;
    }

    // Initialize backtrace structure
    memset(backtrace, 0, sizeof(thread_backtrace_t));
    backtrace->thread_id = pid;

    // Get the executable path if we don't have it yet
    if (executable_path[0] == '\0') {
        if (!get_process_executable(pid, executable_path, sizeof(executable_path))) {
            debug_print("Failed to get executable path for process %d\n", pid);
        } else {
            debug_print("Executable path: %s\n", executable_path);
        }
    }

    // Capture stack frames
    void* frames[MAX_BACKTRACE_DEPTH] = {0};
    int frame_count = unwind_stack_fp(pid, frames, MAX_BACKTRACE_DEPTH);
    backtrace->frame_count = frame_count;

    // Process each frame
    for (int i = 0; i < frame_count; i++) {
        backtrace->frames[i].address = frames[i];

        // Get symbol information if available
        symbol_info_t symbol;
        if (find_symbol_info(frames[i], &symbol)) {
            strncpy(backtrace->frames[i].symbol_name, symbol.name, MAX_SYMBOL_LENGTH - 1);
            backtrace->frames[i].symbol_addr = symbol.addr;
            backtrace->frames[i].offset = symbol.offset;
            
            // Add function marker if it's a function symbol
            if (symbol.is_function && symbol.offset > 0) {
                size_t name_len = strlen(backtrace->frames[i].symbol_name);
                if (name_len < MAX_SYMBOL_LENGTH - 20) {
                    snprintf(backtrace->frames[i].symbol_name + name_len, 
                            MAX_SYMBOL_LENGTH - name_len, "+0x%lx", symbol.offset);
                }
            }
        } else {
            snprintf(backtrace->frames[i].symbol_name, MAX_SYMBOL_LENGTH, "??");
            backtrace->frames[i].symbol_addr = NULL;
            backtrace->frames[i].offset = 0;
        }
    }

    return frame_count > 0;
}

bool backtrace_capture_all_threads(pid_t pid, thread_backtrace_t* backtraces,
                                 size_t max_threads, size_t* thread_count) {
    char task_path[64];
    snprintf(task_path, sizeof(task_path), "/proc/%d/task", pid);

    DIR* dir = opendir(task_path);
    if (!dir) {
        perror("opendir");
        return false;
    }

    // Collect all thread IDs
    struct dirent* entry;
    pid_t thread_ids[max_threads];
    size_t count = 0;

    while ((entry = readdir(dir)) != NULL && count < max_threads) {
        if (entry->d_name[0] != '.') {
            thread_ids[count++] = atoi(entry->d_name);
        }
    }

    closedir(dir);
    *thread_count = count;

    // Capture backtrace for each thread
    size_t success_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (backtrace_capture(thread_ids[i], &backtraces[i])) {
            success_count++;
        }
    }

    return success_count > 0;
}

bool backtrace_is_waiting_for_mutex(const thread_backtrace_t* backtrace, void** mutex_addr) {
    if (backtrace == NULL || backtrace->frame_count == 0) {
        return false;
    }

    // Initialize mutex_addr if provided
    if (mutex_addr != NULL) {
        *mutex_addr = NULL;
    }

    // Look for mutex waiting patterns in the backtrace
    bool found_mutex_wait = false;
    int mutex_frame_index = -1;
    
    for (int i = 0; i < backtrace->frame_count; i++) {
        const char* name = backtrace->frames[i].symbol_name;

        // Check for functions that indicate waiting for a mutex
        if (strstr(name, "pthread_mutex_lock") != NULL ||
            strstr(name, "__lll_lock_wait") != NULL ||
            strstr(name, "__lll_lock_wait_private") != NULL ||
            strstr(name, "futex_wait") != NULL ||
            strstr(name, "__pthread_mutex_lock_full") != NULL) {
            
            found_mutex_wait = true;
            mutex_frame_index = i;
            break;
        }
        
        // Also check for specific futex operations
        if (strstr(name, "futex") != NULL && 
            (strstr(name, "wait") != NULL || strstr(name, "WAIT") != NULL)) {
            found_mutex_wait = true;
            mutex_frame_index = i;
            break;
        }
    }

    if (found_mutex_wait && mutex_addr != NULL) {
        // Try to extract mutex address heuristically
        // In a real implementation, this would require more sophisticated
        // analysis of register state and stack memory
        
        // For now, we use the frame address as a proxy for the mutex
        // This is not accurate but provides some identification
        if (mutex_frame_index >= 0) {
            *mutex_addr = backtrace->frames[mutex_frame_index].address;
        }
    }

    // Additional check: verify this looks like a blocking operation
    if (found_mutex_wait) {
        // Check if we're deep enough in the call stack to suggest blocking
        bool has_blocking_context = false;
        
        for (int i = mutex_frame_index; i < backtrace->frame_count; i++) {
            const char* name = backtrace->frames[i].symbol_name;
            
            // Look for scheduler/kernel context that suggests blocking
            if (strstr(name, "schedule") != NULL ||
                strstr(name, "wait") != NULL ||
                strstr(name, "sleep") != NULL ||
                strstr(name, "block") != NULL ||
                strstr(name, "futex") != NULL) {
                has_blocking_context = true;
                break;
            }
        }
        
        return has_blocking_context;
    }

    return false;
}

bool backtrace_detect_deadlocks(thread_backtrace_t* backtraces, size_t thread_count) {
    if (backtraces == NULL || thread_count == 0) {
        return false;
    }

    // Structure to track mutex waiting patterns
    typedef struct {
        pid_t thread_id;
        void* waiting_for_mutex;
        void* held_mutexes[16];
        int held_count;
    } thread_mutex_state_t;

    thread_mutex_state_t thread_states[thread_count];
    int waiting_thread_count = 0;

    // Analyze each thread's mutex state
    for (size_t i = 0; i < thread_count; i++) {
        thread_states[i].thread_id = backtraces[i].thread_id;
        thread_states[i].waiting_for_mutex = NULL;
        thread_states[i].held_count = 0;

        // Check if thread is waiting for a mutex
        void* mutex_addr;
        if (backtrace_is_waiting_for_mutex(&backtraces[i], &mutex_addr)) {
            thread_states[i].waiting_for_mutex = mutex_addr;
            waiting_thread_count++;
            
            // Try to identify held mutexes from the backtrace
            // This is heuristic-based since we can't easily determine
            // which mutexes a thread currently holds from backtrace alone
            for (int j = 0; j < backtraces[i].frame_count && j < 16; j++) {
                const char* name = backtraces[i].frames[j].symbol_name;
                
                // Look for patterns that suggest mutex ownership
                if (strstr(name, "pthread_mutex_lock") != NULL ||
                    strstr(name, "__lll_lock_wait") != NULL) {
                    // Found a lock operation - previous frames might show held locks
                    // This is a simplified heuristic
                    if (j > 0 && thread_states[i].held_count < 15) {
                        // Use frame address as a proxy for mutex identification
                        thread_states[i].held_mutexes[thread_states[i].held_count++] = 
                            backtraces[i].frames[j-1].address;
                    }
                }
            }
        }
    }

    // If we have fewer than 2 waiting threads, no deadlock
    if (waiting_thread_count < 2) {
        return false;
    }

    debug_print("Found %d threads waiting for mutexes\n", waiting_thread_count);

    // Look for circular wait patterns
    bool deadlock_found = false;
    
    for (int i = 0; i < waiting_thread_count; i++) {
        if (thread_states[i].waiting_for_mutex == NULL) continue;
        
        // For each waiting thread, check if any other thread might be
        // holding the mutex it's waiting for while also waiting for something
        for (int j = 0; j < waiting_thread_count; j++) {
            if (i == j || thread_states[j].waiting_for_mutex == NULL) continue;
            
            // Check if thread j might be holding what thread i is waiting for
            for (int k = 0; k < thread_states[j].held_count; k++) {
                // This is a simplified check - in reality we'd need better
                // mutex identification
                if (thread_states[j].held_mutexes[k] != NULL) {
                    // Found a potential circular dependency
                    debug_print("Potential circular wait: Thread %d waiting for mutex, "
                              "Thread %d holding mutex while waiting\n",
                              thread_states[i].thread_id, thread_states[j].thread_id);
                    deadlock_found = true;
                }
            }
        }
    }

    // Additional heuristic: if multiple threads are blocked in mutex operations
    // and we see evidence of complex locking patterns, likely deadlock
    if (!deadlock_found && waiting_thread_count >= 2) {
        int complex_patterns = 0;
        for (size_t i = 0; i < thread_count; i++) {
            // Count threads with deep call stacks involving mutex operations
            int mutex_frames = 0;
            for (int j = 0; j < backtraces[i].frame_count; j++) {
                const char* name = backtraces[i].frames[j].symbol_name;
                if (strstr(name, "mutex") != NULL || strstr(name, "lock") != NULL ||
                    strstr(name, "futex") != NULL) {
                    mutex_frames++;
                }
            }
            if (mutex_frames >= 2) {
                complex_patterns++;
            }
        }
        
        if (complex_patterns >= 2) {
            debug_print("Complex mutex patterns detected in %d threads\n", complex_patterns);
            deadlock_found = true;
        }
    }

    if (deadlock_found) {
        debug_print("Deadlock pattern detected!\n");
        
        // Print details for all waiting threads
        for (size_t i = 0; i < thread_count; i++) {
            void* mutex_addr;
            if (backtrace_is_waiting_for_mutex(&backtraces[i], &mutex_addr)) {
                fprintf(stderr, "Thread %d waiting for a mutex. Stack trace:\n", backtraces[i].thread_id);
                backtrace_print(&backtraces[i]);
                fprintf(stderr, "\n");
            }
        }
    }

    return deadlock_found;
}

void backtrace_print(const thread_backtrace_t* backtrace) {
    if (backtrace == NULL) {
        return;
    }

    printf("Thread %d backtrace (%d frames):\n", backtrace->thread_id, backtrace->frame_count);

    for (int i = 0; i < backtrace->frame_count; i++) {
        const stack_frame_t* frame = &backtrace->frames[i];

        if (frame->offset > 0) {
            printf("#%d: %p %s+%lx\n", i, frame->address, frame->symbol_name, frame->offset);
        } else {
            printf("#%d: %p %s\n", i, frame->address, frame->symbol_name);
        }
    }
}

void backtrace_set_use_debug_symbols(bool enable) {
    use_debug_symbols = enable;
}
