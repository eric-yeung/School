/*Eric Yeung and Rikin Katyal
104392784
104762347
Program that takes in an 32 bit address as an argument with a 4-KB page size and
returns the page number and offset
*/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGE_SIZE 4096 // 4KB = 4096 bytes

int main(int argc, char const* argv[])
{
    unsigned long address, page, offset; // setting all variables to store 32 bits 

    address = atol(argv[1]);
    page = address / PAGE_SIZE;
    offset = address % PAGE_SIZE;

    printf("Address %lu contains:\n", address);
    printf("Page number = %lu\n", page);
    printf("Offset = %lu\n", offset);

    return 0;
}