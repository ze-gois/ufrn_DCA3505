execve("/usr/bin/gcc", ["gcc", "-static", "-o", "write_c", "write_c.c"], 0x7ffebc32ec10 /* 52 vars */) = 0
brk(NULL)                               = 0x15ba2000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=120219, ...}) = 0
mmap(NULL, 120219, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f07f574d000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0px\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
fstat(3, {st_mode=S_IFREG|0755, st_size=2006328, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f07f574b000
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
mmap(NULL, 2030680, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f07f555b000
mmap(0x7f07f557f000, 1507328, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x24000) = 0x7f07f557f000
mmap(0x7f07f56ef000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x194000) = 0x7f07f56ef000
mmap(0x7f07f573d000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e1000) = 0x7f07f573d000
mmap(0x7f07f5743000, 31832, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f07f5743000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f07f5558000
arch_prctl(ARCH_SET_FS, 0x7f07f5558740) = 0
set_tid_address(0x7f07f5558a10)         = 379155
set_robust_list(0x7f07f5558a20, 24)     = 0
rseq(0x7f07f5558680, 0x20, 0, 0x53053053) = 0
mprotect(0x7f07f573d000, 16384, PROT_READ) = 0
mprotect(0x561000, 8192, PROT_READ)     = 0
mprotect(0x7f07f57a8000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f07f574d000, 120219)          = 0
getrandom("\xe1\x32\xbe\x63\x5a\xfd\xae\x82", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x15ba2000
brk(0x15bc3000)                         = 0x15bc3000
brk(0x15be5000)                         = 0x15be5000
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=3063024, ...}) = 0
mmap(NULL, 3063024, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f07f5200000
close(3)                                = 0
openat(AT_FDCWD, "/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=2998, ...}) = 0
read(3, "# Locale name alias data base.\n#"..., 4096) = 2998
read(3, "", 4096)                       = 0
close(3)                                = 0
openat(AT_FDCWD, "/usr/share/locale/en_US.UTF-8/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/en_US.utf8/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/en_US/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/en.UTF-8/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/en.utf8/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/en/LC_MESSAGES/gcc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
ioctl(2, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
ioctl(0, TIOCGWINSZ, {ws_row=39, ws_col=192, ws_xpixel=1536, ws_ypixel=858}) = 0
ioctl(2, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
ioctl(2, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
rt_sigaction(SIGINT, {sa_handler=SIG_IGN, sa_mask=[INT], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGINT, {sa_handler=0x40bf70, sa_mask=[INT], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_IGN, sa_mask=[INT], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=SIG_IGN, sa_mask=[HUP], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGHUP, {sa_handler=0x40bf70, sa_mask=[HUP], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_IGN, sa_mask=[HUP], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, 8) = 0
rt_sigaction(SIGTERM, {sa_handler=SIG_IGN, sa_mask=[TERM], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTERM, {sa_handler=0x40bf70, sa_mask=[TERM], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_IGN, sa_mask=[TERM], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[PIPE], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGPIPE, {sa_handler=0x40bf70, sa_mask=[PIPE], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_IGN, sa_mask=[PIPE], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, 8) = 0
rt_sigaction(SIGCHLD, {sa_handler=SIG_DFL, sa_mask=[CHLD], sa_flags=SA_RESTORER|SA_RESTART, sa_restorer=0x7f07f5598ef0}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
prlimit64(0, RLIMIT_STACK, {rlim_cur=65536*1024, rlim_max=RLIM64_INFINITY}, NULL) = 0
brk(0x15c06000)                         = 0x15c06000
access("/home/gois/back/lang/sh/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.local/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/back/lang/sh/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.local/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.cargo/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/usr/local/bin/gcc", X_OK)      = -1 ENOENT (No such file or directory)
access("/usr/bin/gcc", X_OK)            = 0
newfstatat(AT_FDCWD, "/usr/bin/gcc", {st_mode=S_IFREG|0755, st_size=1459464, ...}, 0) = 0
readlink("/usr", 0x7ffdd0ce0620, 1023)  = -1 EINVAL (Invalid argument)
readlink("/usr/bin", 0x7ffdd0ce0620, 1023) = -1 EINVAL (Invalid argument)
readlink("/usr/bin/gcc", 0x7ffdd0ce0620, 1023) = -1 EINVAL (Invalid argument)
access("/home/gois/back/lang/sh/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.local/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/back/lang/sh/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.local/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/home/gois/.cargo/bin/gcc", X_OK) = -1 ENOENT (No such file or directory)
access("/usr/local/bin/gcc", X_OK)      = -1 ENOENT (No such file or directory)
access("/usr/bin/gcc", X_OK)            = 0
newfstatat(AT_FDCWD, "/usr/bin/gcc", {st_mode=S_IFREG|0755, st_size=1459464, ...}, 0) = 0
readlink("/usr", 0x7ffdd0ce0620, 1023)  = -1 EINVAL (Invalid argument)
readlink("/usr/bin", 0x7ffdd0ce0620, 1023) = -1 EINVAL (Invalid argument)
readlink("/usr/bin/gcc", 0x7ffdd0ce0620, 1023) = -1 EINVAL (Invalid argument)
getcwd("/mnt/backup/acad/ufrn/DCA3505/hub/z_atividade/tarefa2", 1024) = 54
readlink("/mnt/backup/acad/ufrn/DCA3505/hub/z_atividade/tarefa2/write_c.c", 0x7ffdd0ce0860, 1023) = -1 EINVAL (Invalid argument)
getcwd("/mnt/backup/acad/ufrn/DCA3505/hub/z_atividade/tarefa2", 1024) = 54
readlink("/mnt/backup/acad/ufrn/DCA3505/hub/z_atividade/tarefa2/write_c", 0x7ffdd0ce0860, 1023) = -1 EINVAL (Invalid argument)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/", X_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/", X_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/specs", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/specs", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/specs", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/specs", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/", X_OK) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/lto-wrapper", {st_mode=S_IFREG|0755, st_size=1190616, ...}, 0) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/lto-wrapper", X_OK) = 0
access("/tmp", R_OK|W_OK|X_OK)          = 0
newfstatat(AT_FDCWD, "/tmp", {st_mode=S_IFDIR|S_ISVTX|0777, st_size=860, ...}, 0) = 0
rt_sigprocmask(SIG_BLOCK, ~[], [], 8)   = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_DROPPABLE|MAP_ANONYMOUS, -1, 0) = 0x7f07f576a000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f07f5769000
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
getrandom("\xd6\x90\xd4\x26\x2f\x9e\x16\x74\xd6\xdd\x96\xa6\xc7\xee\xd5\x91\xd4\x67\x52\x7f\xcc\x3a\xbd\x9f\x33\xc3\x7d\x11\x9a\xce\x80\x90", 32, 0) = 32
openat(AT_FDCWD, "/tmp/ccY8Ro1I.s", O_RDWR|O_CREAT|O_EXCL, 0600) = 3
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/cc1", {st_mode=S_IFREG|0755, st_size=45699952, ...}, 0) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/cc1", X_OK) = 0
mmap(NULL, 36864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0x7f07f5760000
rt_sigprocmask(SIG_BLOCK, ~[], [], 8)   = 0
clone3({flags=CLONE_VM|CLONE_VFORK|CLONE_CLEAR_SIGHAND, exit_signal=SIGCHLD, stack=0x7f07f5760000, stack_size=0x9000}, 88) = 379156
munmap(0x7f07f5760000, 36864)           = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
wait4(379156, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 379156
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=379156, si_uid=1000, si_status=0, si_utime=1 /* 0.01 s */, si_stime=0} ---
openat(AT_FDCWD, "/tmp/ccWqA1J4.o", O_RDWR|O_CREAT|O_EXCL, 0600) = 3
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/bin/x86_64-pc-linux-gnu/15.1.1/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/bin/as", 0x7ffdd0ce1b70, 0) = -1 ENOENT (No such file or directory)
mmap(NULL, 36864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0x7f07f5760000
rt_sigprocmask(SIG_BLOCK, ~[], [], 8)   = 0
clone3({flags=CLONE_VM|CLONE_VFORK|CLONE_CLEAR_SIGHAND, exit_signal=SIGCHLD, stack=0x7f07f5760000, stack_size=0x9000}, 88) = 379157
munmap(0x7f07f5760000, 36864)           = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
wait4(379157, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 379157
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=379157, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/collect2", {st_mode=S_IFREG|0755, st_size=568024, ...}, 0) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/collect2", X_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/liblto_plugin.so", R_OK) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/bin/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/bin/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/../lib/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/lib/../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/.", 0x7ffdd0ce1a70, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
openat(AT_FDCWD, "/tmp/cc73JtrU.res", O_RDWR|O_CREAT|O_EXCL, 0600) = 3
close(3)                                = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/crt1.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/crt1.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/../lib/crt1.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../x86_64-pc-linux-gnu/15.1.1/crt1.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../lib/crt1.o", R_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/crti.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/crti.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/../lib/crti.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../x86_64-pc-linux-gnu/15.1.1/crti.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../lib/crti.o", R_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/crtbeginT.o", R_OK) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/.", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/../lib/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/lib/../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/x86_64-pc-linux-gnu/15.1.1/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/../lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/.", 0x7ffdd0ce0b10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/.", {st_mode=S_IFDIR|0755, st_size=143360, ...}, 0) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/crtend.o", R_OK) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/crtn.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/x86_64-pc-linux-gnu/15.1.1/crtn.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../x86_64-pc-linux-gnu/lib/../lib/crtn.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../x86_64-pc-linux-gnu/15.1.1/crtn.o", R_OK) = -1 ENOENT (No such file or directory)
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/../../../../lib/crtn.o", R_OK) = 0
newfstatat(AT_FDCWD, "/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/collect2", {st_mode=S_IFREG|0755, st_size=568024, ...}, 0) = 0
access("/usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/collect2", X_OK) = 0
mmap(NULL, 36864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0x7f07f5760000
rt_sigprocmask(SIG_BLOCK, ~[], [], 8)   = 0
clone3({flags=CLONE_VM|CLONE_VFORK|CLONE_CLEAR_SIGHAND, exit_signal=SIGCHLD, stack=0x7f07f5760000, stack_size=0x9000}, 88) = 379158
munmap(0x7f07f5760000, 36864)           = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
wait4(379158, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 379158
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=379158, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
newfstatat(AT_FDCWD, "/tmp/cc73JtrU.res", {st_mode=S_IFREG|0600, st_size=0, ...}, 0) = 0
unlink("/tmp/cc73JtrU.res")             = 0
newfstatat(AT_FDCWD, "/tmp/ccWqA1J4.o", {st_mode=S_IFREG|0600, st_size=1528, ...}, 0) = 0
unlink("/tmp/ccWqA1J4.o")               = 0
newfstatat(AT_FDCWD, "/tmp/ccY8Ro1I.s", {st_mode=S_IFREG|0600, st_size=580, ...}, 0) = 0
unlink("/tmp/ccY8Ro1I.s")               = 0
exit_group(0)                           = ?
+++ exited with 0 +++
