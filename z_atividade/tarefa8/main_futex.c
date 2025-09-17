#include <stdatomic.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>

#define SPIN_LIMIT 100

atomic_int trava = 0;

static int futex_wait(atomic_int *addr, int val) {
    return syscall(SYS_futex, addr, FUTEX_WAIT, val, NULL, NULL, 0);
}

static int futex_wake(atomic_int *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, n, NULL, NULL, 0);
}

void enter_region(void) {
    int expected;

    for (int i = 0; i < SPIN_LIMIT; ++i) {
        expected = 0;
        if (atomic_compare_exchange_weak(&trava, &expected, 1))
            return; // acquired
        __asm__ __volatile__("pause");
    }

    while (1) {
        expected = 0;
        if (atomic_compare_exchange_strong(&trava, &expected, 1))
            return;

        futex_wait(&trava, 1);
    }
}

void leave_region(void) {
    atomic_store(&trava, 0);
    futex_wake(&trava, 1);
}
