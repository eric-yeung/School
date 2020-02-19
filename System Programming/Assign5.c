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
void buildCommmand(char *com, char *comArgv[10]) //tokenizer for the seperated commands
{

  const char a[2] = " "; //delimiter is space
  char *token;
  int i = 0;

  token = strtok(com, a);
  
  while (token != NULL)//tokenizes it and stores into an array of strings
  {
    comArgv[i] = token;
    i++;
    token = strtok(NULL, a);
  }
  comArgv[i] = NULL;

}

int main(int argc, char *argv[]){
  int fd[2];
  char *comArgv1[10], *comArgv2[10]; //need two arrays for both arguments
  char *token, *com1, *com2;
  const char s[2] = "|";

  token = strtok(argv[1], s);
  
  com1 = token;
  token = strtok(NULL, s);

  com2 = token;
  token = strtok(NULL, s);
  
  buildCommmand(com1, comArgv1); //builds the two arrays
  buildCommmand(com2, comArgv2);

  if(pipe(fd)==-1){
    perror("Cannot create pipe: ");
    exit(1);
  }
  if(fork() > 0){
    parent(fd, comArgv1); //pass the first set of commands
  }
  else
    child(fd, comArgv2);//pass second set
}

void parent(int *fd, char *argv[]){ // A writer
  close(fd[0]);
  dup2(fd[1], 1); // 1 is the standard output
  close(fd[1]); // close original file descriptor

  if(execvp(argv[0], argv) == -1){ //use execvp for changeable number arguements since execlp only took a certain amount
    perror("Cannot exec: ");
    exit(3);
  }
}
void child(int *fd, char *argv[]){ // A reader
  close(fd[1]);
  dup2(fd[0], 0); // 0 is the standard input
  close(fd[0]); // close original file descriptor

  if(execvp(argv[0], argv) == -1){
    perror("Cannot exec: "); 
    exit(3);
  }
}