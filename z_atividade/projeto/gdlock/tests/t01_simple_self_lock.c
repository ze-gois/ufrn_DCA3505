#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t pt_id = pthread_self();
    printf("[%ld] Starting simple lock ordering test\n", pt_id);

    printf("Acquiring mutex\n");
    pthread_mutex_lock(&mutex);

    printf("Acquiring the same mutex (creating self dependency)\n");
    pthread_mutex_lock(&mutex);

    printf("Releasing mutex\n");
    pthread_mutex_unlock(&mutex);

    printf("Releasing mutex\n");
    pthread_mutex_unlock(&mutex);

    printf("Test completed\n");
    return 0;
}
