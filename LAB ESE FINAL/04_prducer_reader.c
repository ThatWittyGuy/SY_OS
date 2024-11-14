#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
sem_t S;
int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void* arg)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%100;
        sem_wait(&empty);
        sem_wait(&S);
        buffer[in] = item;
        printf("Producer : Insert Item %d at %d\n",buffer[in],in);
        in = (in+1)%BufferSize;
        sem_post(&S);
        sem_post(&full);
    }
}
void *consumers(void* arg)
{
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        sem_wait(&S);
        int item = buffer[out];
        printf("Consumer: Remove Item %d from %d\n",item, out);
        out = (out+1)%BufferSize;
        sem_post(&S);
        sem_post(&empty);
    }
}

int main()
{

    pthread_t prod, cons;

    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
    sem_init(&S,0,1);

    pthread_create(&prod, NULL, (void *)producer, NULL);
    pthread_create(&cons, NULL, (void *)consumers, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&S);

    return 0;

}

// Reader - Writer code

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    sem_post(&wrt);
}

void *reader(void *rno)
{   
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   
    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10};

    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
