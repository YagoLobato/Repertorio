#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define NUM_IT 20

int buffer[TAM_BUFFER];
int in = 0, out = 0;
int count = 0;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        buffer[in] = i;
        printf("Produzido: %d em %d\n", i, in);
        in = (in + 1) % TAM_BUFFER;
        count++;

        printf("Thread Produtora: [TID %ld] contador = %d\n\n", pthread_self(), count);
        usleep(rand() % 100000);
    }

    sleep(rand() % 10);
    printf("Thread Produtora finalizada.\n");
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        int item = buffer[out];
        printf("Consumido: %d de %d\n", item, out);
        out = (out + 1) % TAM_BUFFER;
        count--;

        printf("Thread Consumidora: [TID %ld], contador = %d\n\n", pthread_self(), count);
        usleep(rand() % 150000);
    }

    sleep(rand() % 10);
    printf("Thread Consumidora finalizada.\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    if (count == 0) {
        printf("Buffer terminou vazio, contador: %d.\n", count);
    } else {
        printf("Buffer não terminou vazio, contador: %d.\n", count);
    }
    
    return 0;
}
