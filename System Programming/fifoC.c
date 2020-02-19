#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd, fd2, n;
	char ch;
	char message[100];

	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_WRONLY);

	do{
		fprintf(stderr, "Enter a message for server\n");
		n = read(0, message, 100);
		if (n <= 0)
			break;
		message[n] = '\0';
		if(write(fd2, message, n+1) <= 0){
			break;
		}
		fprintf(stderr, "Do not type: Waiting for server\n");
		n = read(fd, message, 100);
		if (n > 0){
			fprintf(stderr, "Received message from server: %s\n", message);
		}

	}while(n > 0);
	close(fd);
	close(fd2);
	return 0;
}