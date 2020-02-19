/*Eric Yeung
Program that takes input from user for file to be copied
and allows them to specify the copied file's new name
while also checking if the 1st file exists as well as if 
the copied file doesn't already exist*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

const int buffer = 4095;
#define srcmessage "Source file: "
#define desmessage "Destination file: "
#define src_error_message "Error with input name. "
#define des_error_message "Error with destination name. "
#define error_1 "Cannot open file. "
#define error_2 "Cannot create destination file. "

int main(int argc, char const *argv[])
{
	char source[buffer]; //buffers for file source and new file name
	char dest[buffer];
	char data[buffer];

	int filesource;
	int filedest;

	write(STDOUT_FILENO, srcmessage, sizeof(srcmessage));
	int src_r = read(STDIN_FILENO, source, buffer); //gets string from keyboard for file to be copied;
	
	if (src_r == -1) //error checking for source input
	{
		write(STDOUT_FILENO, src_error_message, sizeof(src_error_message));
	}
	
	int len1 = src_r;
	source[len1 - 1] = '\0'; //sets the end of the string to a null character

	write(STDOUT_FILENO, desmessage, sizeof(desmessage));
	int dest_r = read(STDIN_FILENO, dest, buffer); //gets string from keyboard for new copied file name

	if (dest_r == -1)
	{
		write(STDOUT_FILENO, des_error_message, sizeof(des_error_message));
	}
	
	int len2 = dest_r;
	dest[len2 - 1] = '\0';

	filesource = open(source, O_RDONLY, 0700); //opens file source in read only mode
	filedest = open(dest, O_CREAT | O_WRONLY | O_EXCL, 0700);//creates new file with name specified by user
	
	if (filesource == -1) //checks if file exists, if not then program terminates
	{
		write(STDOUT_FILENO, error_1, sizeof(error_1));
		exit(0);
	} 

	else if (filedest == -1)
	{
		write(STDOUT_FILENO, error_2, sizeof(error_2));
		exit(0);
	} 

	while (read(filesource, data, buffer) != 0) //loops until read function reaches EOF then terminates
	{
		write(filedest, data, strlen(data)); //writes data to destination 
	}

	printf("File has been copied.\n"); 

	close(filesource);
	close(filedest);
	return 0;
}