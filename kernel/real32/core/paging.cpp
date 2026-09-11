#include "paging.h"

static volatile unsigned int* page_directory = reinterpret_cast<volatile unsigned int*>(0x9000);
static bool enabled = false;

void paging_init()
{
    for (unsigned int index = 0; index < 1024; ++index)
        page_directory[index] = 0;

    for (unsigned int index = 0; index < 256; ++index)
        page_directory[index] = (index * 0x400000) | 0x083;

    unsigned int cr4;
    unsigned int cr0;
    asm volatile("mov %%cr4, %0" : "=r"(cr4));
    cr4 |= 1u << 4;
    asm volatile("mov %0, %%cr4" : : "r"(cr4));
    asm volatile("mov %0, %%cr3" : : "r"(page_directory));
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 1u << 31;
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
    enabled = true;
}

bool paging_enabled()
{
    return enabled;
}
