#include "exceptions.h"
#include "idt.h"
#include "panic.h"
#include "../drivers/vga.h"

extern "C" void exception_divide_stub();
extern "C" void exception_invalid_opcode_stub();
extern "C" void exception_general_protection_stub();
extern "C" void exception_page_fault_stub();

void exceptions_init()
{
    idt_set_gate(0, reinterpret_cast<unsigned int>(exception_divide_stub));
    idt_set_gate(6, reinterpret_cast<unsigned int>(exception_invalid_opcode_stub));
    idt_set_gate(13, reinterpret_cast<unsigned int>(exception_general_protection_stub));
    idt_set_gate(14, reinterpret_cast<unsigned int>(exception_page_fault_stub));
}

extern "C" void exception_dispatch(unsigned int vector)
{
    vga_set_color(15, 4);
    vga_clear();
    vga_set_cursor(20, 5);
    vga_print("EDORA CPU EXCEPTION");
    vga_set_cursor(8, 9);
    vga_print("Vector: ");
    vga_putc(static_cast<char>('0' + (vector / 10)));
    vga_putc(static_cast<char>('0' + (vector % 10)));
    vga_set_cursor(8, 11);
    vga_print("Paging and IDT caught the fault.");
    vga_set_cursor(8, 15);
    vga_print("System halted safely.");
    kernel_panic("CPU exception");
}
