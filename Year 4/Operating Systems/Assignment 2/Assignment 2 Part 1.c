/*Eric Yeung
Creates a child process that is exited without waiting, therefore creating
a zombie process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
const int time = 10;

#define message1 "\nThis is the parent process\n"
#define message2 "\nThis is the child process\n"

int main(void)
{
	pid_t child_pid;

	child_pid = fork();

	if(child_pid > 0) //checking for parent process
	{
		write(STDOUT_FILENO, message1, sizeof(message1));
		sleep(time); //sleeps the program so I can check in terminal that it is there with ps command

	}

	else  //checking for child process 
	{
		write(STDOUT_FILENO, message2, sizeof(message2));
		exit(0);
	}


	return 0;
}

