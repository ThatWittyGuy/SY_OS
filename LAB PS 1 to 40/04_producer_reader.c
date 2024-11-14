#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITERATIONS 10  

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *param) {
    int item, count = 0;
    while (count < ITERATIONS) {
        item = rand() % 100;  
        sem_wait(&empty);      
        sem_wait(&mutex);      
        buffer[in] = item;     
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);      
        sem_post(&full);      
        count++;
    }
    return NULL;
}


void *consumer(void *param) {
    int item, count = 0;
    while (count < ITERATIONS) {
        sem_wait(&full);       
        sem_wait(&mutex);      
        item = buffer[out];    
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);      
        sem_post(&empty);      
        count++;
    }
    return NULL;
}

void *reader(void *param) {
    int id = *((int *)param);  
    int count = 0;
    while (count < ITERATIONS) {
        sem_wait(&mutex);      
        printf("Reader %d is reading\n", id);
        sem_post(&mutex);      
        sleep(1);
        count++;
    }
    return NULL;
}

void *writer(void *param) {
    int count = 0;
    while (count < ITERATIONS) {
        sem_wait(&empty);      
        sem_wait(&mutex);      
        printf("Writer is writing\n");
        sem_post(&mutex);      
        sem_post(&empty);      
        sleep(1);
        count++;
    }
    return NULL;
}

void menu() {
    printf("\nSelect an operation:\n");
    printf("1. Producer-Consumer\n");
    printf("2. Reader-Writer\n");
    printf("3. Exit\n");
}

int main() {
    pthread_t prod, cons, r1, r2, r3, r4, w;
    int choice;
    int reader1_id = 1, reader2_id = 2, reader3_id = 3, reader4_id = 4;

    sem_init(&empty, 0, BUFFER_SIZE);  
    sem_init(&full, 0, 0);             
    sem_init(&mutex, 0, 1);            

    while (1) {
        menu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Running Producer-Consumer...\n");

                // Create producer and consumer threads
                pthread_create(&prod, NULL, producer, NULL);
                pthread_create(&cons, NULL, consumer, NULL);

                // Wait for threads to finish
                pthread_join(prod, NULL);
                pthread_join(cons, NULL);
                break;

            case 2:
                printf("Running Reader-Writer...\n");

                // Create reader threads with unique IDs
                pthread_create(&r1, NULL, reader, &reader1_id);
                pthread_create(&r2, NULL, reader, &reader2_id);
                pthread_create(&r3, NULL, reader, &reader3_id);
                pthread_create(&r4, NULL, reader, &reader4_id);

                // Create writer thread
                pthread_create(&w, NULL, writer, NULL);

                // Wait for threads to finish
                pthread_join(r1, NULL);
                pthread_join(r2, NULL);
                pthread_join(r3, NULL);
                pthread_join(r4, NULL);
                pthread_join(w, NULL);
                break;

            case 3:
                printf("Exiting...\n");
                sem_destroy(&empty);
                sem_destroy(&full);
                sem_destroy(&mutex);
                return 0;

            default:
                printf("Invalid choice! Please select between 1 and 3.\n");
        }
    }

    return 0;
}
