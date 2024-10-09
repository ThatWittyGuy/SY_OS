#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t mutex;

void* philosopher(void* arg) {
    int i = *((int*)arg);
    while (1) {
        printf("Philosopher %d is thinking.\n", i);
        sleep(rand() % 5);
        
        sem_wait(&mutex);
        sem_wait(&forks[i]);
        sem_wait(&forks[(i+1)%N]);
        
        printf("Philosopher %d is eating.\n", i);
        sleep(rand() % 5);
        
        sem_post(&forks[i]);
        sem_post(&forks[(i+1)%N]);
        sem_post(&mutex);
    }
}

int main() {
    pthread_t threads[N];
    int ids[N];
    
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }
    
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    
    return 0;
}
