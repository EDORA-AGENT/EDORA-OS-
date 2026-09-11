#include "process.h"
#include "../drivers/vga.h"

struct Process
{
    unsigned int pid;
    const char* name;
    const char* state;
};

static Process process_table[8];
static unsigned int process_total = 0;
static volatile unsigned int current_process = 0;

void process_init()
{
    process_total = 3;
    process_table[0] = {0, "idle", "running"};
    process_table[1] = {1, "kernel", "running"};
    process_table[2] = {2, "shell", "waiting"};
    current_process = 1;
}

unsigned int process_count()
{
    return process_total;
}

void process_scheduler_tick()
{
    if (process_total == 0)
        return;

    current_process = (current_process + 1) % process_total;
}

unsigned int process_current()
{
    return current_process;
}

void process_list()
{
    vga_print("PID   STATE     NAME\n");
    for (unsigned int index = 0; index < process_total; ++index)
    {
        const Process& process = process_table[index];
        vga_putc(static_cast<char>('0' + process.pid));
        vga_print("     ");
        vga_print(process.state);
        vga_print("   ");
        vga_print(process.name);
        vga_print("\n");
    }
}
