#include "paging.h"
uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void paging_init()
{
    //set each entry to not present
    // This sets the following flags to the pages:
    //   Supervisor: Only kernel-mode can access them
    //   Write Enabled: It can be both read from and written to
    //   Not Present: The page table is not present
    for (unsigned int i=0;i<1024;++i)
        page_directory[i]=0x00000002;

    //we will fill all 1024 entries in the table, mapping 4 megabytes
    for(unsigned int i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
    }
    // attributes: supervisor level, read/write, present
    page_directory[0] = ((unsigned int)first_page_table) | 3;

    //loads the page directory address onto the CR3 register, where the MMU will find it
    __asm__ volatile("mov cr3, %0\n\t"
    : 
    : "r" (page_directory));

    //enabling paging (changing 32th bit of cr0)
    __asm__ volatile("mov eax, cr0");
    __asm__ volatile("or eax, 0x80000000");
    __asm__ volatile("mov cr0, eax");
}
