#include "ram.h"

static const unsigned int RAM_START = 0x100000;
static const unsigned int RAM_END = 32 * 1024 * 1024;
static unsigned int next_address = RAM_START;

void ram_init()
{
    next_address = RAM_START;
}

unsigned int ram_total_mb()
{
    return RAM_END / (1024 * 1024);
}

unsigned int ram_used_kb()
{
    return (next_address - RAM_START) / 1024;
}

unsigned int ram_free_kb()
{
    return (RAM_END - next_address) / 1024;
}

void* ram_alloc(unsigned int size)
{
    if (size == 0 || size > RAM_END - next_address)
        return 0;

    unsigned int address = next_address;
    next_address += (size + 7) & ~7u;
    return reinterpret_cast<void*>(address);
}
