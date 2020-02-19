#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int readline (int fd, char buff[], int size){ //readline function
	int totalread = 0;
	int numread = 0;

	while ((numread = read (fd, buff + totalread, size - totalread)) > 0){
		totalread += numread;
	}
	return ((numread < 0 ) ? numread : totalread);
}

int main(int argc, char *argv[])
{
	int file = open("script.txt", O_RDONLY); //opens file for read only

	if (file == NULL) //checks if file is valid otherwise quits
	{
		perror("Error opening file.");
		return(-1);
	}

	int n = 0;
	char line[255];
	char *myCommand[10];
	int i, j;

	while(1)
	{
		n = readline(file, line, 255);

		if (n <= 0)
		{
			break;
		}
		if (line[0] == '#' || line[0] == '\n') //checks for empty line or comment
		{
			n = 0;
			break;
		}

		line[n - 1] = '\0';
 
		i = j = 0;
		myCommand[i] = (char *) malloc(25);
		while (sscanf(line + j, "%s", myCommand[i] == -1)) //scans line for commands
		{
			j += strlen(myCommand[i]);
			while (line[j] == ' ')
			{
				j++;
			}
			i++;
			myCommand[i] = (char *) malloc(25);
		}
		myCommand[i] = NULL;

		if (!fork())
		{
			if (execvp(myCommand[0], myCommand) == -1) //execs myCommand with arguments in myCommand
			{
				exit(3);
			}
		}
		wait (&status); //waits on the child to end

		if (n == -1) //checks if there was an error reading
		{
			perror("Error reading.");
			break;
		}
	}
}