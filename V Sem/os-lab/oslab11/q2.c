#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define MAXR 5
#define MAXT 10

int avail[MAXR], maxneed[MAXT][MAXR], alloc[MAXT][MAXR], need[MAXT][MAXR];
int nT, nR;
pthread_mutex_t lock;

bool is_safe() {
    int work[MAXR]; bool finish[MAXT] = {0};
    for (int i = 0; i < nR; i++) work[i] = avail[i];
    while (1) {
        bool found = false;
        for (int i = 0; i < nT; i++) {
            if (!finish[i]) {
                bool can = true;
                for (int j = 0; j < nR; j++)
                    if (need[i][j] > work[j]) can = false;
                if (can) {
                    for (int j = 0; j < nR; j++) work[j] += alloc[i][j];
                    finish[i] = found = true;
                }
            }
        }
        if (!found) break;
    }
    for (int i = 0; i < nT; i++) if (!finish[i]) return false;
    return true;
}

void* run(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&lock);
        int req[MAXR]; bool valid = true;
        for (int i = 0; i < nR; i++) {
            req[i] = rand() % (need[id][i] + 1);
            if (req[i] > avail[i]) valid = false;
        }
        if (valid) {
            for (int i = 0; i < nR; i++) {
                avail[i] -= req[i];
                alloc[id][i] += req[i];
                need[id][i] -= req[i];
            }
            if (is_safe()) printf("T%d granted\n", id);
            else {
                for (int i = 0; i < nR; i++) {
                    avail[i] += req[i];
                    alloc[id][i] -= req[i];
                    need[id][i] += req[i];
                }
                printf("T%d denied (unsafe)\n", id);
            }
        } else printf("T%d denied (insufficient)\n", id);
        pthread_mutex_unlock(&lock);

        usleep(rand() % 500000);

        pthread_mutex_lock(&lock);
        for (int i = 0; i < nR; i++) {
            int rel = rand() % (alloc[id][i] + 1);
            alloc[id][i] -= rel;
            need[id][i] += rel;
            avail[i] += rel;
        }
        printf("T%d released\n", id);
        pthread_mutex_unlock(&lock);

        usleep(rand() % 500000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    printf("Enter threads & resources: ");
    scanf("%d %d", &nT, &nR);
    printf("Enter available: ");
    for (int i = 0; i < nR; i++) scanf("%d", &avail[i]);
    printf("Enter max need:\n");
    for (int i = 0; i < nT; i++)
        for (int j = 0; j < nR; j++) {
            scanf("%d", &maxneed[i][j]);
            need[i][j] = maxneed[i][j];
            alloc[i][j] = 0;
        }
    pthread_mutex_init(&lock, NULL);
    pthread_t t[MAXT]; int id[MAXT];
    for (int i = 0; i < nT; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, run, &id[i]);
    }
    for (int i = 0; i < nT; i++) pthread_join(t[i], NULL);
    pthread_mutex_destroy(&lock);
}

