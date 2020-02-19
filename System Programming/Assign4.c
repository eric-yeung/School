//Eric Yeung
//Program to do arithmetic operations using read, write, fork, wait


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void childFunction(char *line){
	write(1,"I am a child working for my parent\n", 36);
	float a, b;
	float answer;
	char operator;
	char buf[250];

	int check = sscanf(line, "%f %c %f", &a, &operator, &b); //check for at least 3 arguments

	if(check != 3)
	{
		exit(50);
	}

	else if(operator == '/' && b == 0) // checks for divsion and 0 to exit
	{
		exit(100);
	}

	else if(operator != '+' && operator != '-' && operator != '*' && operator != '/') //checks the operator is a valid one
	{
		exit(200);
	}
	else{
		switch(operator){ //use switch statements to choose which operator to use 
			case '+' :
				answer = a + b; 
				break;
			case '-' :
				answer = a - b;
				break;
			case '*' :
				answer = a * b;
				break;
			case '/' :
				answer = a / b;
				break;
		}
	}

	sprintf(buf, "%f%c%f = %.2f\n", a, operator, b, answer);
	write(1, buf, strlen(buf));
	exit(0);
}


int main(int argc, char *argv[]){
	

	while(1){

		char line[250];

		write(1,"Enter an arithmetic statement, eg., 34+ 132 > ", 46);

		read(STDIN_FILENO, line, 250);
		int n;

		if(fork()){ //this is the parent
			write(1, "Created a child to make your operation, waiting\n", 49);
			wait(&n);
			int errorcode = WEXITSTATUS(n); //returns exit code to errorcode and we use that to check which code

			if(errorcode == 50){
				write(1, "Wrong statement\n", 17);
			}
			else if(errorcode == 100){
				write(1, "Division by zero\n", 18);
			}
			else if(errorcode == 200){
				write(1, "Wrong operator\n", 15);
			}
		}

		else{//this is the child
			childFunction(line);
		}
	}
	return 0;
}



