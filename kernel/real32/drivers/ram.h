#ifndef EDORA_RAM_H
#define EDORA_RAM_H

void ram_init();
unsigned int ram_total_mb();
unsigned int ram_used_kb();
unsigned int ram_free_kb();
void* ram_alloc(unsigned int size);

#endif
