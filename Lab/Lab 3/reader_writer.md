The Reader-Writer problem is a classic synchronization issue in operating systems that deals with how multiple processes can read from and write to a shared resource, such as a database or file. The main challenge is to allow concurrent access for multiple readers while ensuring that only one writer can access the resource at a time. Moreover, if a writer is writing, no readers should be allowed to read.

## Key Concepts

1. **Readers**: Multiple readers can access the shared resource simultaneously without causing issues since they do not modify the data.
2. **Writers**: Only one writer can access the shared resource at a time, and no readers can access it while a writer is writing.

### Cases to Consider

- **Case 1**: Two writers cannot write simultaneously.
- **Case 2**: A writer cannot write while a reader is reading.
- **Case 3**: A reader cannot read while a writer is writing.
- **Case 4**: Multiple readers can read simultaneously.

## Solution using Semaphores

To implement a solution for the Reader-Writer problem, we can use semaphores to manage access to the shared resource. We will use three variables:

- `mutex`: To ensure mutual exclusion when updating the count of readers.
- `wrt`: To control access for writers.
- `read_count`: To keep track of the number of active readers.

### C Code Snippet

Here's a simple implementation of the Reader-Writer problem in C:

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5

sem_t mutex; // Semaphore for mutual exclusion
sem_t wrt;   // Semaphore for writers
int read_count = 0; // Number of active readers

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex); // Enter critical section
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt); // First reader locks the writer
        }
        sem_post(&mutex); // Exit critical section

        // Reading section
        printf("Reader %d is reading.\n", id);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Enter critical section
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // Last reader unlocks the writer
        }
        sem_post(&mutex); // Exit critical section
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&wrt); // Wait for access to write

        // Writing section
        printf("Writer %d is writing.\n", id);
        sleep(1); // Simulate writing time

        sem_post(&wrt); // Release the writer
    }
}

int main() {
    pthread_t readers[MAX_READERS], writers[2];
    int reader_ids[MAX_READERS], writer_ids[2];

    sem_init(&mutex, 0, 1); // Initialize mutex semaphore
    sem_init(&wrt, 0, 1);   // Initialize writer semaphore

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (not usually reached in this infinite loop example)
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex); // Clean up
    sem_destroy(&wrt);
    return 0;
}
```

### Explanation of the Code

- **Semaphores**: `mutex` ensures mutual exclusion when updating `read_count`, while `wrt` controls access for writers.
- **Reader Function**: Each reader waits for `mutex` to enter the critical section, increments `read_count`, and if it's the first reader, it waits for `wrt`. After reading, it decrements `read_count`, and if it's the last reader, it releases `wrt`.
- **Writer Function**: The writer waits for `wrt` to gain exclusive access, performs its writing task, and then releases `wrt`.
- **Main Function**: Initializes semaphores, creates reader and writer threads, and waits for them to finish.

This implementation ensures that multiple readers can read simultaneously while writers have exclusive access to write, thus solving the Reader-Writer problem effectively.

Citations:
[1] https://www.prepbytes.com/blog/operating-system/reader-writer-problem-in-os/
[2] https://www.geeksforgeeks.org/readers-writers-problem-set-1-introduction-and-readers-preference-solution/
[3] https://www.javatpoint.com/os-readers-writers-problem
[4] https://www.tutorialspoint.com/readers-writers-problem
[5] https://www.scaler.com/topics/operating-system/producer-consumer-problem-in-os/