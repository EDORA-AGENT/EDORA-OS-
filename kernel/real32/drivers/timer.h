#ifndef EDORA_TIMER_H
#define EDORA_TIMER_H

void timer_init(unsigned int frequency);
unsigned int timer_frequency();
unsigned long timer_ticks();
void timer_set_frequency(unsigned int frequency);
void timer_irq_handler();

#endif
