[0;34m================================================[0m
[0;34m   Enhanced Lockdep Build and Test System      [0m
[0;34m================================================[0m


[0;36mChecking Dependencies[0m
[0;36m=====================[0m

Required dependencies: ✓
libelf (optional): ✓ - Enhanced symbol resolution enabled
[1;33mptrace permissions: ⚠ - May need 'echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope'[0m

[0;36mBuilding Project[0m
[0;36m================[0m

Cleaning previous build...
Configuring with CMake...
-- The C compiler identification is GNU 15.1.1
-- The CXX compiler identification is GNU 15.1.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found PkgConfig: /usr/bin/pkg-config (found version "2.5.1")
-- Checking for module 'libelf'
--   Found libelf, version 0.193
-- Found libelf: enhanced symbol resolution enabled
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/gois/back/acad/ufrn/DCA3505/hub/z_atividade/projeto/lockdep/build
Building project...
[ 13%] Building C object CMakeFiles/t02_classic_deadlock.dir/src/tests/t02_classic_deadlock.c.o
[ 10%] Building C object CMakeFiles/t08_deadlock_avoidance_trylock.dir/src/tests/t08_deadlock_avoidance_trylock.c.o
[ 10%] Building C object CMakeFiles/t09_deadlock_avoidance_timeout.dir/src/tests/t09_deadlock_avoidance_timeout.c.o
[ 16%] Building C object CMakeFiles/t06_dynamic_locks.dir/src/tests/t06_dynamic_locks.c.o
[ 33%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/backtrace.c.o
[ 16%] Building C object CMakeFiles/t01_simple_lock_order.dir/src/tests/t01_simple_lock_order.c.o
[ 36%] Building C object CMakeFiles/lockdep_interpose.dir/src/graph/graph.c.o
[ 40%] Building C object CMakeFiles/t07_recursive_locks.dir/src/tests/t07_recursive_locks.c.o
[ 20%] Building C object CMakeFiles/t05_dining_philosophers.dir/src/tests/t05_dining_philosophers.c.o
[ 23%] Building C object CMakeFiles/t04_circular_deadlock.dir/src/tests/t04_circular_deadlock.c.o
[ 43%] Building C object CMakeFiles/lockdep_interpose.dir/src/interpose/pthread_interpose.c.o
[ 46%] Building C object CMakeFiles/lockdep_interpose.dir/src/lockdep/lockdep_core.c.o
[ 26%] Building C object CMakeFiles/t03_nested_deadlock.dir/src/tests/t03_nested_deadlock.c.o
[ 30%] Building C object CMakeFiles/ptrace-lockdep.dir/src/graph/graph.c.o
[ 50%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/main.c.o
[ 53%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/lock_tracker.c.o
[ 60%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/ptrace_attach.c.o
[ 60%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/pthread_structures.c.o
[ 63%] Building C object CMakeFiles/ptrace-lockdep.dir/src/ptrace/syscall_intercept.c.o
[ 66%] Linking C executable ptrace-lockdep
[  3%] Building C object CMakeFiles/lockdep_interpose.dir/src/graph/graph.c.o
