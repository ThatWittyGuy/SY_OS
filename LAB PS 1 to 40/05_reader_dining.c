#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_PHILOSOPHERS 5
#define ITERATIONS 10

sem_t mutex, wrt;
int read_count = 0;

sem_t forks[NUM_PHILOSOPHERS];

void *reader(void *param) {
    int id = *((int *)param);
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void *writer(void *param) {
    while (1) {
        sem_wait(&wrt);

        printf("Writer is writing\n");
        sleep(1);

        sem_post(&wrt);

        sleep(1);
    }
    return NULL;
}

void *philosopher(void *param) {
    int id = *((int *)param);
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        sleep(1);
    }
    return NULL;
}

void menu() {
    printf("\nSelect an operation:\n");
    printf("1. Reader-Writer\n");
    printf("2. Dining Philosophers\n");
    printf("3. Exit\n");
}

int main() {
    pthread_t r_threads[NUM_READERS], w_thread;
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int choice, i;
    int reader_ids[NUM_READERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    while (1) {
        menu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Running Reader-Writer...\n");

                for (i = 0; i < NUM_READERS; i++) {
                    reader_ids[i] = i + 1;
                    pthread_create(&r_threads[i], NULL, reader, &reader_ids[i]);
                }
                pthread_create(&w_thread, NULL, writer, NULL);

                for (i = 0; i < NUM_READERS; i++) {
                    pthread_join(r_threads[i], NULL);
                }
                pthread_join(w_thread, NULL);
                break;

            case 2:
                printf("Running Dining Philosophers...\n");

                for (i = 0; i < NUM_PHILOSOPHERS; i++) {
                    pthread_create(&philosophers[i], NULL, philosopher, &i);
                }

                for (i = 0; i < NUM_PHILOSOPHERS; i++) {
                    pthread_join(philosophers[i], NULL);
                }
                break;

            case 3:
                printf("Exiting...\n");
                sem_destroy(&mutex);
                sem_destroy(&wrt);
                for (i = 0; i < NUM_PHILOSOPHERS; i++) {
                    sem_destroy(&forks[i]);
                }
                return 0;

            default:
                printf("Invalid choice! Please select between 1 and 3.\n");
        }
    }

    return 0;
}
