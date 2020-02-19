#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	pid_t newid;
	pid_t childpid;
	pid_t childpid2;

	pid = getpid(); //parent id

	childpid = fork();

	newid = getpid();

	if(pid == newid)
	{
		childpid2 = fork();
	}

	newid = getpid();

	if(pid != newid)
	{
		printf("%d %d\n", getpid(), getppid());
	}
	
	else
	{
		sleep(1);
		printf("Parent: %d, Child1: %d, Child2: %d\n", getpid(), childpid, childpid2);		
	}

return 0;
}