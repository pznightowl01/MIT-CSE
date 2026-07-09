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

    shmp->flag = 0;
    shmp->message[0] = '\0';

    while (1) {
        char buffer[SHM_SIZE];
        printf("Enter your message: ");

        if (fgets(buffer, SHM_SIZE, stdin) == NULL) break;
        buffer[strcspn(buffer, "\n")] = '\0';

        while (shmp->flag == 1) sleep(1);

        strcpy(shmp->message, buffer);
        shmp->flag = 1;

        if (strcmp(buffer, "end") == 0) break;
    }

    shmdt(shmp);
    return 0;
}

