// Prdocuer Consumer in C

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}


// Reader - Writer code

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int data = 0, readcnt = 0;

void *reader(void *arg){
	int f;
	f = ((intptr_t)arg);
	sem_wait(&mutex);
	readcnt += 1;
	if (readcnt == 1)
		sem_wait(&wrt);
	sem_post(&mutex);
	printf("Data read by the reader%d is %d\n",f,data);
	sleep(1);
	sem_wait(&mutex);
	readcnt -= 1;
	if(readcnt == 0)
		sem_post(&wrt);
	sem_post(&mutex);
}

void *writer(void *arg){
	int f;
	f = ((intptr_t)arg);
	sem_wait(&wrt);
	data++;
	printf("Data written by the writer%d is %d\n",f, data);
	sleep(1);
	sem_post(&wrt);
}

int main(){
	int i, b;
	pthread_t rtid[5], wtid[5];
	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);
	for (i=0;i<=2;i++){
		pthread_create(&wtid[i], NULL, writer, (void *)(intptr_t)i);
		pthread_create(&rtid[i], NULL, reader, (void *)(intptr_t)i);
	}
	for (i=0;i<=2;i++){
		pthread_join(wtid[i], NULL);
		pthread_join(rtid[i], NULL);
	}
	return 0;
}