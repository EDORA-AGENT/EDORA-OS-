#ifndef EDORA_PROCESS_H
#define EDORA_PROCESS_H

void process_init();
void process_list();
unsigned int process_count();
void process_scheduler_tick();
unsigned int process_current();

#endif
