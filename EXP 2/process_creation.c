#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
    int pid = fork();

    if (pid > 0) {
        wait(NULL);
        printf("Parent process is running\n");
        printf("Process id : %d\n\n", getpid());
    } else if (pid == 0 ) {
        printf("Child process is running\n");
        printf("Process id : %d\n", getpid());
        printf("Parent id : %d\n\n", getppid());
    } else {
        printf("Error\n");
        printf("Exiting");
        exit(0);
    }
}

/*
Child process is running
Process id : 1253
Parent id : 1252

Parent process is running
Process id : 1252
*/
