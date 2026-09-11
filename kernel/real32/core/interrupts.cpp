#include "interrupts.h"
#include "idt.h"
#include "pic.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "exceptions.h"
#include "process.h"

void interrupts_init()
{
    idt_init();
    exceptions_init();
    pic_init();
    idt_enable();
    asm volatile("sti");
}

extern "C" void interrupt_dispatch(unsigned int vector)
{
    if (vector == 32)
    {
        timer_irq_handler();
        process_scheduler_tick();
        pic_end_of_interrupt(0);
    }
    else if (vector == 33)
    {
        keyboard_irq_handler();
        pic_end_of_interrupt(1);
    }
}
