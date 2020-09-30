/*Eric Yeung and Rikin Katyal
104392784
104762347
Program that uses 1,000,000 32 bit addresses and a 4-KB page size
and calculates the total time it takes to compute through it all
*/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int runValue = 1000000; // constant max run value
#define PAGE_SIZE 4096 // 4KB = 4096 bits

int main(int argc, char const* argv[])
{
    unsigned long address, page, offset; // setting all variables to store 32 bits
    
    clock_t start, end; // for the timer
    double cpu_time_used;

    unsigned long randMax = pow(2, 32) - 1; // defining the max random value
    
    srand(time(0)); // seeder for random number generator 
    start = clock(); // start timer

    for (int i = 0; i < runValue; i++)
    { 
        address = (rand() % randMax); // random number between 0 and 2^32 - 1
        page = address / PAGE_SIZE;
        offset = address % PAGE_SIZE;
    }
    
    end = clock(); // end timer
    cpu_time_used = ((double) (end - start));
    double time_taken = ((double)cpu_time_used)/CLOCKS_PER_SEC;

    printf("Time taken: %f\n", time_taken);

    return 0;
}