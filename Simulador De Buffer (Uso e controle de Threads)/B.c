#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define TAM_BUFFER 5
#define NUM_IT 20

int buffer[TAM_BUFFER];
int in = 0, out = 0;
int count = 0; 

sem_t mutex; 
sem_t vazio; 
sem_t cheio;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {

        sem_wait(&vazio);
        sem_wait(&mutex);
        buffer[in] = i;

        printf("Produzido: %d em %d\n", i, in);

        in = (in + 1) % TAM_BUFFER;
        count++;

        printf("Thread Produtora: [TID %ld] contador = %d\n\n", pthread_self(), count);
        sem_post(&mutex);
        sem_post(&cheio);

        usleep(rand() % 100000);
    }

    sleep(rand() % 10);
    printf("\nThread Produtora %ld finalizada.\n", pthread_self());
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {

        sem_wait(&cheio);
        sem_wait(&mutex);
        int item = buffer[out];

        printf("Consumido: %d de %d\n", item, out);

        out = (out + 1) % TAM_BUFFER;
        count--;

        printf("Thread Consumidora: [TID %ld] contador = %d\n\n", pthread_self(), count);
        sem_post(&mutex);
        sem_post(&vazio);

        usleep(rand() % 150000);
    }

    sleep(rand() % 10);
    printf("\nThread Consumidora %ld finalizada.\n", pthread_self());
    return NULL;
}

int main() {

    sem_init(&mutex, 0, 1);           
    sem_init(&vazio, 0, TAM_BUFFER);  
    sem_init(&cheio, 0, 0);   


    pthread_t t1, t2;
    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    if (count == 0) {
        printf("\nBuffer terminou vazio, contador: %d.\n", count);
    } else {
        printf("\nBuffer não terminou vazio, contador: %d.\n", count);
    }

    sem_destroy(&mutex);
    sem_destroy(&vazio);
    sem_destroy(&cheio);
    return 0;
}
