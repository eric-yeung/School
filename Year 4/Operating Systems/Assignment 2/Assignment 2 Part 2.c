/*Eric Yeung
Creates a child process that is exited without waiting, therefore creating
a zombie process.
Program will also find zombie processes and show them, then kill the parent of
any zombie process, then display the updated list of processes with their states
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define message1 "\nUpdated List of Processes\n"

int main(void)
{
	system ("./A2a &");
	system ("ps -l");
	sleep(3);
	
	system("kill -9 $(ps -l|grep -w Z|tr -s U+0020|cut -c 18-22)");
	sleep(7);
	
	write(STDOUT_FILENO, message1, sizeof(message1));
	system ("ps -l");
	
	return 0;
}

