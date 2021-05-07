/*Eric Yeung, Joseph Varacalli, Matt Prieur
A program that tranlates logical addresses into physical addresses
for a 2^16 virtual address space. Uses a TLB and a page table to do this
Also has FIFO algorithm to deal with page faults 
Also uses bitwise operations for max SPEEDDDDDDD*/

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining constants
#define TLB_SIZE 16
#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256

#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define MEMORY_SIZE PAGES * PAGE_SIZE
#define BUF_SIZE 10


struct tlbEntry //structure for TLB entry; is basically an queue system following FIFO
{
	unsigned char logical;
	unsigned char physical;
};

struct tlbEntry tlb[TLB_SIZE];

int tlbIndex = 0;

int max (int a, int b) //max function since C doesnt have one
{
	if (a > b)
	{
		return a;
	}
	return b;
}

int search_TLB(unsigned char logical_page) //gives us the physical address from TLB; if not there then returns -1
{
	int i;
	for (i = max ((tlbIndex - TLB_SIZE), 0); i < tlbIndex; i++)
	{
		struct tlbEntry *entry = &tlb[i % TLB_SIZE];
		if (entry->logical == logical_page)
		{
			return entry->physical;
		}
		
	}
	return -1;
}

void add_To_TLB(unsigned char logical, unsigned char physical)
{
	//adds the mapping to TLB, following FIFO and replacing the oldest one
	struct tlbEntry *entry = &tlb[tlbIndex % TLB_SIZE];
	tlbIndex++;
	entry->logical = logical;
	entry->physical = physical;
}

int pagetable[PAGES];

signed char main_memory[MEMORY_SIZE];
signed char *backing_ptr;

int main(int argc, char const* argv[])
{
	for (int i = 0; i < PAGES; i++) //fills pagetable so its for sure empty
	{
		pagetable[i] = -1;
	}

	int total_addr = 0, pageFault = 0, tlb_hits = 0;

	const char *file_name = argv[1];
	const char *input_file = argv[2];
	const char *output_file = "output.txt";

	int backing_ptr_fd = open(file_name, O_RDONLY); //opening our backing store file
	backing_ptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_ptr_fd, 0); //creating a memory map

	FILE *input_fp = fopen(input_file, "r");
	FILE *output_fp = fopen(output_file, "w");

	char buf[BUF_SIZE];

	unsigned char freePage = 0;

	while (fgets(buf, BUF_SIZE, input_fp) != NULL)
	{
		int logicalAddress = atoi(buf); //reads input from txt file
		
		//bitwise operations
		int offset = logicalAddress & OFFSET_MASK;
		int logical = (logicalAddress >> OFFSET_BITS) & PAGE_MASK;
		int physical = search_TLB(logical);

		total_addr++;
		if (physical != -1) //checks for a TLB hit
		{
			tlb_hits++;
		}
		else
		{
			physical = pagetable[logical];

			if (physical == -1) //for page faults
			{
				pageFault++;

				physical = freePage;
				freePage++;

				memcpy(main_memory + physical * PAGE_SIZE, backing_ptr + logical * PAGE_SIZE, PAGE_SIZE);

				pagetable[logical] = physical;
			}
			
			add_To_TLB(logical, physical);
		}

		int physicalAddress = (physical << OFFSET_BITS) | offset; //figure out the physical address
		signed char value = main_memory[physical * PAGE_SIZE + offset];

		fprintf(output_fp, "Logical address: %d Physical Address: %d Value: %d\n", logicalAddress, physicalAddress, value); //prints output to an output file
	}
	
	printf("Number of Translated Addresses = %d\n", total_addr);
	printf("Page faults = %d\n", pageFault);
	printf("Page Fault Rate = %.1f %% \n", (pageFault / (total_addr*1.) * 100));
	 printf("TLB Hits = %d\n", tlb_hits);
    printf("TLB Hit Rate = %.3f %%\n", tlb_hits / (1. * total_addr) * 100);

	
}