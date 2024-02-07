#include <stdio.h>
#include <unistd.h>

int main() {
	int id = fork();
	if(id>0) {
		printf("Parent process running\n");
		printf("Parent id : %d\n\n", getpid());
	}
	else if(id==0) {
		printf("Child process running\n");
		printf("Child id : %d\n", getpid());
		printf("Parent id : %d\n\n", getppid());
	}
	else {
		printf("Error\n");
		printf("Exiting");
	}
}

