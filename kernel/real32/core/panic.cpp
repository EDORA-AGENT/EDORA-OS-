#include "panic.h"
#include "../drivers/vga.h"

[[noreturn]] void kernel_panic(const char* reason)
{
    vga_set_color(15, 4);
    vga_clear();
    vga_set_cursor(24, 5);
    vga_print("EDORA KERNEL PANIC");
    vga_set_color(15, 4);
    vga_set_cursor(8, 9);
    vga_print("The kernel stopped because of an unrecoverable error.");
    vga_set_cursor(8, 11);
    vga_print("Reason: ");
    vga_print(reason ? reason : "unknown error");
    vga_set_cursor(8, 15);
    vga_print("System halted.");

    asm volatile("cli");
    while (true)
        asm volatile("hlt");
}
