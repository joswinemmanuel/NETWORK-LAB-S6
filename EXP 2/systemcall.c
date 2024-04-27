#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"./sample", NULL};
    execvp(args[0], args);
}

/*
joswin@LAPTOP:~$ gcc sample.c -o sample
joswin@LAPTOP:~$ gcc systemcall.c -o systemcall
joswin@LAPTOP:~$ ./systemcall
Running sample.c using systemcall.c
*/
