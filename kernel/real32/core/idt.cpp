#include "idt.h"

struct IdtEntry
{
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short offset_high;
} __attribute__((packed));

struct IdtPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

extern "C" void interrupt_default_stub();
extern "C" void interrupt_timer_stub();
extern "C" void interrupt_keyboard_stub();

static IdtEntry idt[256];
static IdtPointer idt_pointer;

void idt_set_gate(unsigned char vector, unsigned int handler)
{
    idt[vector].offset_low = static_cast<unsigned short>(handler & 0xFFFF);
    idt[vector].selector = 0x08;
    idt[vector].zero = 0;
    idt[vector].flags = 0x8E;
    idt[vector].offset_high = static_cast<unsigned short>((handler >> 16) & 0xFFFF);
}

void idt_init()
{
    for (unsigned int vector = 0; vector < 256; ++vector)
        idt_set_gate(static_cast<unsigned char>(vector), reinterpret_cast<unsigned int>(interrupt_default_stub));

    idt_set_gate(32, reinterpret_cast<unsigned int>(interrupt_timer_stub));
    idt_set_gate(33, reinterpret_cast<unsigned int>(interrupt_keyboard_stub));

    idt_pointer.limit = sizeof(idt) - 1;
    idt_pointer.base = reinterpret_cast<unsigned int>(&idt[0]);
}

void idt_enable()
{
    asm volatile("lidt %0" : : "m"(idt_pointer));
}
