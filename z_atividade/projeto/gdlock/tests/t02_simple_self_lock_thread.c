#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* arg){

    printf("Acquiring mutex\n");
    pthread_mutex_lock(&mutex);

    printf("Acquiring the same mutex (creating self in thread)\n");
    pthread_mutex_lock(&mutex);

    printf("Releasing mutex\n");
    pthread_mutex_unlock(&mutex);

    printf("Releasing mutex\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    printf("Starting simple lock ordering test\n");

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread, NULL);

    pthread_join(thread_id, NULL);
    printf("Test completed\n");
    return 0;
}
