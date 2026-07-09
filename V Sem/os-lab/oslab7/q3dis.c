#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define KEY 1234

struct shmseg {
    int flag;
    char message[SHM_SIZE];
};

int main() {
    int shmid = shmget(KEY, sizeof(struct shmseg), 0666 | IPC_CREAT);
    if (shmid == -1) exit(1);

    struct shmseg *shmp = (struct shmseg*) shmat(shmid, NULL, 0);
    if (shmp == (void*) -1) exit(1);

    while (1) {
        if (shmp->flag == 1) {
            if (strcmp(shmp->message, "end") == 0) break;
            printf("Received: %s\n", shmp->message);
            shmp->flag = 0;
            shmp->message[0] = '\0';
        }
        sleep(1);
    }

    shmdt(shmp);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

