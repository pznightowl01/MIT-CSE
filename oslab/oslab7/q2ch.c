#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shmcm.h"

int main() {
    int shmid;
    struct shared_use_st *shared_stuff;
    void *shared_memory = (void *)0;

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    shared_stuff = (struct shared_use_st *)shared_memory;

    while (1) {
        
        if (shared_stuff->done == 0) {
            
            if (shared_stuff->alphabet == 'Z') {
                shared_stuff->alphabet = 'A';
            } else if (shared_stuff->alphabet == 'z') {
                shared_stuff->alphabet = 'a';
            } else {
                shared_stuff->alphabet += 1;
            }
            shared_stuff->done = 1;
            printf("Child processed and updated the character to: %c\n", shared_stuff->alphabet);
            break;
        }
        sleep(1);
    }

    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

