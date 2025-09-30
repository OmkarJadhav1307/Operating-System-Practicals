#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_SLOTS 3
#define NUM_CARS 6

sem_t slots;

void* car(void* arg) {
    int id = *(int*)arg;
    sem_wait(&slots);
    printf("Car %d parked\n", id);
    sleep(2);
    printf("Car %d leaving\n", id);
    sem_post(&slots);
    return NULL;
}

int main() {
    pthread_t tid[NUM_CARS];
    int ids[NUM_CARS];

    sem_init(&slots, 0, NUM_SLOTS);

    for (int i = 0; i < NUM_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&tid[i], NULL, car, &ids[i]);
    }
    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&slots);
    return 0;
}
