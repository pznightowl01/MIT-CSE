#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 20
int buf[5], f = -1, r = -1;

sem_t mutex, full, empty, prod_lead;

void *produce(void *arg)
{
    int i;
    for(i=0; i<MAX; i++)
    {
        sem_wait(&prod_lead);
        sem_wait(&empty);
        sem_wait(&mutex);

        buf[(++r) % 5] = i;
        printf("Produced item: %d\n", i);

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consume(void *arg)
{
    int item, i;
    for(i=0; i<MAX; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buf[(++f) % 5];
        printf("Consumed item: %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);
        sem_post(&prod_lead);
        sleep(2);
    }
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    sem_init(&prod_lead, 0, 10);
    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consume, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&prod_lead);

    return 0;
}

