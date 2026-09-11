#ifndef EDORA_IDT_H
#define EDORA_IDT_H

void idt_init();
void idt_set_gate(unsigned char vector, unsigned int handler);
void idt_enable();

#endif
