#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];  // споделен буфер
int count = 0;  // брой на продуктите в буфера
int iterations = 0;  // брой итерации

// инициализиране на mutex и condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);

        if(iterations >= 100) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        while(count == BUFFER_SIZE) {
            pthread_cond_wait(&can_produce, &mutex);
        }

        buffer[count++] = 1;  // прави продукт
        printf("Producer produces, count = %d\n", count);

        pthread_cond_signal(&can_consume);
        pthread_mutex_unlock(&mutex);

        iterations++;
    }
}

void* consumer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);

        if(iterations >= 100) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        while(count == 0) {
            pthread_cond_wait(&can_consume, &mutex);
        }

        buffer[--count] = 0;  // консумира продукт
        printf("Consumer consumes, count = %d\n", count);

        pthread_cond_signal(&can_produce);
        pthread_mutex_unlock(&mutex);

        iterations++;
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
