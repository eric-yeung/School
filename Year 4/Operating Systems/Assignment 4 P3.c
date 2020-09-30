/*Eric Yeung and Rikin Katyal
104392784
104762347
Program that takes in 3 arguments, the address space, the page size in bytes
and the address and outputs the page number and offset
*/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char const* argv[])
{
    unsigned long long address, page, offset, pageSize; // setting all variables to store 64 bits
    int addressSpace;
    
    addressSpace = atoi(argv[1]);
    pageSize = atoll(argv[2]);
    address = atoll(argv[3]);
    
    if(addressSpace != 16 & addressSpace != 32 & addressSpace != 64) //checking if the address is 16, 32 or 64 bit
    {
        printf("Address space is not 16, 32 or 64\n");
        return -1;
    }

    if((pageSize & (pageSize-1)) != 0) //using bit manipulation to see if the number is a power of 2 
    {
        printf("Page size is not a power of 2\n");
        return -1;
    }

    page = address / pageSize;
    offset = address % pageSize;

    printf("Address %llu contains:\n", address);
    printf("Page number = %llu\n", page);
    printf("Offset = %llu\n", offset);

    return 0;
}