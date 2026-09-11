#include "timer.h"

static volatile unsigned long ticks = 0;
static unsigned int current_frequency = 100;

static void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void timer_set_frequency(unsigned int frequency)
{
    if (frequency < 20)
        frequency = 20;
    if (frequency > 1000)
        frequency = 1000;

    unsigned int divisor = 1193182u / frequency;
    outb(0x43, 0x36);
    outb(0x40, static_cast<unsigned char>(divisor & 0xFF));
    outb(0x40, static_cast<unsigned char>((divisor >> 8) & 0xFF));
    current_frequency = frequency;
}

void timer_init(unsigned int frequency)
{
    ticks = 0;
    timer_set_frequency(frequency);
}

unsigned int timer_frequency()
{
    return current_frequency;
}

unsigned long timer_ticks()
{
    return ticks;
}

void timer_irq_handler()
{
    ++ticks;
}
