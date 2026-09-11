#include "pic.h"

static void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned char inb(unsigned short port)
{
    unsigned char value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void pic_init()
{
    unsigned char master_mask = inb(0x21);
    unsigned char slave_mask = inb(0xA1);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, static_cast<unsigned char>(master_mask & 0xFC));
    outb(0xA1, slave_mask);
}

void pic_end_of_interrupt(unsigned char irq)
{
    if (irq >= 8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
