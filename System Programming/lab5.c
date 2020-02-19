#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){   // To execute
  int status=0, n;                  // commands with no arguments
  char line[255];
  char prompt[30]="Enter your command here> ";
  char *myCommand[10];  // new
  int i, j;             // new

  int file = open("script.command", O_RDONLY);
  if (file == NULL){
    perror("Error opening file.");
    return (-1);
  }
  
  while(1){
    write(file, prompt, 25);
    n=readLine(file, line, 255);
    if (n <= 0) // read a command
      break;

    line[n-1] = '\0';     // get rid of \n and add '\0'
                        // for string manipulation
 
   // change starts over here

    i=j=0;
    myCommand[i]=(char *) malloc(25);
    while (sscanf(line+j, "%s", myCommand[i]) == 1){
      j += strlen(myCommand[i]);
      while (line[j] == ' ')    // skip blanks to keep good count
        j++;
      i++;
      myCommand[i]=(char *) malloc(25);
    }
    myCommand[i]=NULL;

    if(!fork()) 
      if(execvp(myCommand[0], myCommand)==-1){
        perror("child Process");
        exit(3);
      }
    wait(&status);
  }
  if(n==-1)
    perror("Reading error ");

  exit(0);
}

int readLine(int fd, char *buff, int n){
  int i=0, m;

  while(i<n && (m=read(fd, &buff[i], 1))==1){
    if(buff[i]=='\n')
       return(i+1);
    i++;
  }
  if(m == -1)             // Error, return -1
     return(-1);
  else
     return(i);           // number of characters read
}