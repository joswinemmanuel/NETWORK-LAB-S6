
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t p = fork();
    if(p<0) {
      printf("Error");
    }
    printf("Hello world!, process_id(pid) = %d \n", getpid());
}

