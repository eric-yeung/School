#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	int file = open("file.txt", O_RDONLY);
	char data[200];
	pid_t child;
	int check = 0;

	child = fork();
	if (child > 0)
	{
		wait(&check);
	}

	else if (child == 0)
	{
		read(file, data, 9);
		write(1, data, 9);
		sleep(3);
		printf("\n%d\n", getpid());
		printf("\nChild terminating\n");
		sleep(3);
		exit(20);
	}
	printf("My child has terminated. Child process returned: %d\n", check);
	return 0;
}