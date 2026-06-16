#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "No child.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("I'm the child!\n");
        printf("pid is %d\nppid is %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    else { 
        sleep(10);  // keep parent alive so you can test bg/ps
        printf("Complete\n");
        exit(EXIT_SUCCESS);
    }
}

