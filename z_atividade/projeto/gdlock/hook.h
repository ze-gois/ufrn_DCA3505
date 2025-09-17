#include <pthread.h>

typedef int (*real_mutex_lock_t)(pthread_mutex_t *);
typedef int (*real_mutex_unlock_t)(pthread_mutex_t *);
typedef int (*real_mutex_init_t)(pthread_mutex_t *, const pthread_mutexattr_t *);
typedef int (*real_mutex_destroy_t)(pthread_mutex_t *);

void init(void);
void destroy(void);

void pml_pre(pthread_mutex_t *mutex);
int pml_pos(pthread_mutex_t *mutex, int ret);

void pmu_pre(pthread_mutex_t *mutex);
int pmu_pos(pthread_mutex_t *mutex, int ret);

void pmi_pre(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pmi_pos(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr, int ret);

void pmd_pre(pthread_mutex_t *mutex);
int pmd_pos(pthread_mutex_t *mutex, int ret);
