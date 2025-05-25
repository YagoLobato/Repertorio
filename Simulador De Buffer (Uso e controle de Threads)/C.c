#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define NUM_IT 20

int buffer[TAM_BUFFER];
int in = 0, out = 0;
int count = 0;
int total_produzido = 0;
int produtores_ativos = 1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {

        pthread_mutex_lock(&lock);
        while (count == TAM_BUFFER) {
            printf("[Produtor %ld] Buffer cheio. Aguardando...\n\n", pthread_self());
            pthread_cond_wait(&cond_prod, &lock);
        }
        buffer[in] = i;
        printf("Produzido: %d em %d\n", i, in);

        in = (in + 1) % TAM_BUFFER;
        count++;
        total_produzido++;

       
        printf("Thread Produtora: [TID %ld] contador = %d\n\n", pthread_self(), count);
        pthread_cond_signal(&cond_cons);
        pthread_mutex_unlock(&lock);;

        usleep(rand() % 100000);
    }

    pthread_mutex_lock(&lock);
    produtores_ativos--;
    
    if (produtores_ativos == 0) {
        printf("[Sistema] Todos os produtores terminaram. Notificando consumidores...\n\n");
        pthread_cond_broadcast(&cond_cons);
    }
    
    pthread_mutex_unlock(&lock);
    
    sleep(rand() % 10);
    printf("\nThread Produtora %ld finalizada.\n\n", pthread_self());
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {

        pthread_mutex_lock(&lock);
        while (count == 0) {
            if (produtores_ativos == 0 && count == 0) {
                printf("[Consumidor %ld] Não há mais produtores ativos e o buffer está vazio. Encerrando...\n\n", pthread_self());
                pthread_mutex_unlock(&lock);
                return NULL;
            }

            printf("[Consumidor %ld] Buffer vazio. Aguardando...\n\n", pthread_self());
            pthread_cond_wait(&cond_cons, &lock);
            
            if (produtores_ativos == 0 && count == 0) {
                printf("[Consumidor %ld] Acordou, mas não há mais produtores e o buffer está vazio. Encerrando...\n", pthread_self());
                pthread_mutex_unlock(&lock);
                return NULL;
            }
        }

        int item = buffer[out];
        printf("Consumido: %d de %d\n", item, out);

        out = (out + 1) % TAM_BUFFER;
        count--;

        printf("Thread Consumidora: [TID %ld], contador = %d\n\n", pthread_self(), count);
        pthread_cond_signal(&cond_prod);
        pthread_mutex_unlock(&lock);

        usleep(rand() % 150000);
    }

    sleep(rand() % 10);
    printf("\nThread Consumidora %ld finalizada.\n", pthread_self());
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

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_prod);
    pthread_cond_destroy(&cond_cons);
    
    return 0;
}
