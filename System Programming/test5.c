#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>


void parent(int *fd, char *argv[]);
void child(int *fd, char *argv[]);    

int main(int argc, char *argv[]){
  int fd[2];
  
  if(pipe(fd)==-1){
    perror("Cannot create pipe: ");
    exit(1);
  }
  if(fork() > 0)
    parent(fd, argv);
  else
    child(fd, argv);
}

void parent(int *fd, char *argv[]){ // A writer
  close(fd[0]);
  dup2(fd[1], 1); // 1 is the standard output
  close(fd[1]); // close original file descriptor
  if(execlp(argv[1], argv[1], NULL) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}
void child(int *fd, char *argv[]){ // A reader
  close(fd[1]);
  dup2(fd[0], 0); // 0 is the standard input
  close(fd[0]); // close original file descriptor
  if(execlp(argv[2], argv[2], NULL) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}