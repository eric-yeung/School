//Eric Yeung
//104392784
//Program for SIN checking with text file reading using read()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fd = open("sins.txt", O_RDONLY); //opens file
char sinNum [10];
char buff [10]; //buffer for numbers
int sum = 0; //use this numnber to check if valid
int multiplier [] = {1, 2, 1, 2, 1, 2, 1, 2, 1};

int readLine(int fd, char *buff, int size)
{
	int bytes_read; 
	char t;
	int i = 0;
	do 
	{
		bytes_read = read(fd, &t, 1); //reads one byte at a time
		buff[k++] = t; //sends to buffer
		if (t == '\n') //checks end of line
		{
			buff[k] = '\0';
		}
		for (int i = 1; i <= 7; i += 2)
		{
			if (2 * (sinNum[i]-'0') >= 10)
			{
				sum += multiplier[i] * (sinNum[i]-'0') - 9;
			}
			else
			{
				sum += multiplier[i] * (sinNum[i]-'0');
			}
		}	

		for (int i = 0; i <= 8; i += 2)
		{
			sum += sinNum[i]-'0';
		}

		if (sum % 10 == 0)
		{
			char message[10] = "VALID";
			write(2, message, 5);
		}
		else
		{
			char message[10] = "INVALID";
			write(2, message, 7);
		}
	}
	while (bytes_read != 0); //keeps doing it until end of line
}

readLine(fd, simNum, 9);