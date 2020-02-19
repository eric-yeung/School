#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd, fd2;
	int n;
	char message[100];

	unlink(argv[1]);
	unlink(argv[2]);
	if(mkfifo(argv[1], 0777) != 0){
		exit(1);
	}
	if(mkfifo(argv[2], 0777) != 0){
		exit(1);
	}
	chmod(argv[1], 0777);
	chmod(argv[2], 0777);
	while(1){
		fprintf(stderr, "\nWaiting for client\n");
		fd = open(argv[1], O_WRONLY);
		fprintf(stderr, "Got a client\n");
		fd2 = open(argv[2], O_RDONLY);\
		do{

			n = read(fd2, message, 100);
			if(n > 0){
				fprintf(stderr, "\nReceived message: %s\n", message);
				fprintf(stderr, "Enter message for client\n");
				n = read(0, message, 100);
				if(n <= 0){
					break;
				}
				message[n] = '\0';
				if(write(fd, message, n+1) <= 0){
					break;
				}
			}
		}while(n > 0);
		close(fd);
		close(fd2);	
	}
	return 0;
}