#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void buildCommmand(char *com, char *comArgv[10])
{

	const char a[2] = " ";
	char *token;
	int i = 0;

	token = strtok(com, a);
	
	//comArgv[i] = token;
	
	while (token != NULL)
	{
		comArgv[i] = token;
		i++;
		token = strtok(NULL, a);
	}
	comArgv[i] = NULL;

}

int main(int argc, char *argv[])
{
	
	const char s[2] = "|";
	char *comArgv1[10];
	char *comArgv2[10];
	char *token, *com1, *com2;
	int i; 

	token = strtok(argv[1], s);
	com1 = token;
	printf("First command:%s\n", token);

	token = strtok(NULL, s);
	com2 = token;

	printf("Second command:%s\n", token);
	token = strtok(NULL, s);

	buildCommmand(com1, comArgv1);

	printf("First command is made up with:\n");
	i = 0;
	while(comArgv1[i] != NULL){
		printf("%s\n", comArgv1[i]);
		i++;
	}

	buildCommmand(com2, comArgv2);

	printf("Second command is made up with:\n");
	i = 0;
	while(comArgv2[i] != NULL){
		printf("%s\n", comArgv2[i]);
		i++;
	}

	if(!fork()){
		execvp(comArgv1[0], comArgv1);
	}

	sleep(1);
	printf("\n");

	if(!fork()){
		execvp(comArgv2[0], comArgv2);
	}

	return (0);
}

