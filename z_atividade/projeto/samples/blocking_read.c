#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int pipefd1[2]; // Thread 1 lê, Thread 2 escreveria
int pipefd2[2]; // Thread 2 lê, Thread 1 escreveria

void* thread_func1(void* arg) {
    char buf[100];
    printf("Thread 1 esperando dados de Thread 2...\n");
    read(pipefd1[0], buf, sizeof(buf));  // bloqueia aqui
    printf("Thread 1 recebeu: %s\n", buf);

    const char* reply = "Ack from Thread 1";
    write(pipefd2[1], reply, strlen(reply));
    return NULL;
}

void* thread_func2(void* arg) {
    char buf[100];
    printf("Thread 2 esperando dados de Thread 1...\n");
    read(pipefd2[0], buf, sizeof(buf));  // bloqueia aqui
    printf("Thread 2 recebeu: %s\n", buf);

    const char* reply = "Ack from Thread 2";
    write(pipefd1[1], reply, strlen(reply));
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pipe(pipefd1);
    pipe(pipefd2);

    pthread_create(&t1, NULL, thread_func1, NULL);
    pthread_create(&t2, NULL, thread_func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
