#include "paging.h"
uint32_t* page_directory __attribute__((aligned(4096)))= (uint32_t*)PAGE_DIRECTORY_MEMORY_LOCATION; // page directory location
uint32_t* page_table __attribute__((aligned(4096)))= (uint32_t*)PAGE_TABLES_MEMORY_LOCATION; // page tables(4096 bytes each) location

void paging_init()
{
    __asm__ volatile("cli");
    //set each entry to not present
    // This sets the following flags to the pages:
    //   user: user-mode can access them
    //   Write Enabled: It can be both read from and written to
    //   Not Present: The page table is not present
    for (uint32_t i=0;i<1024;++i)
        *(page_directory+i)=0x00000006;

    //we will fill all 1024 entries in the table*1024 tables, mapping 4 GB
    for(uint32_t i = 0; i < 1024*1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes
        *(page_table+i) = (i * 0x1000) | 7; // attributes: user level, read/write, present.
    }
    // attributes: user level, read/write, present
    for(uint32_t i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes
        *(page_directory + i) = ((unsigned int)page_table) | 7;
    }

    //loads the page directory address onto the CR3 register, where the MMU will find it
    __asm__ volatile("mov cr3, %0\n\t"
    : 
    : "r" (page_directory));

    //enabling paging (changing 32th bit of cr0)
    __asm__ volatile("mov eax, cr0");
    __asm__ volatile("or eax, 0x80000000");
    __asm__ volatile("mov cr0, eax");
    __asm__ volatile("sti");
}
