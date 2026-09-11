#ifndef EDORA_INTERRUPTS_H
#define EDORA_INTERRUPTS_H

void interrupts_init();
extern "C" void interrupt_dispatch(unsigned int vector);

#endif
