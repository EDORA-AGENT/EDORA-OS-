
#include "drivers/keyboard.h"
#include "drivers/ata.h"
#include "drivers/ram.h"
#include "drivers/rtl8139.h"
#include "drivers/system.h"
#include "drivers/timer.h"
#include "drivers/vga.h"
#include "core/panic.h"
#include "core/interrupts.h"
#include "core/filesystem.h"
#include "core/process.h"
#include "core/auth.h"
#include "core/paging.h"


// ========================================
// String comparison
// ========================================

static bool equals(const char* a,
                   const char* b)
{
    while (*a && *b)
    {
        if (*a != *b)
            return false;

        a++;
        b++;
    }

    return *a == *b;
}

static bool starts_with(const char* text, const char* prefix)
{
    while (*prefix)
    {
        if (*text++ != *prefix++)
            return false;
    }

    return true;
}

static unsigned int number_from(const char* text)
{
    unsigned int value = 0;

    while (*text >= '0' && *text <= '9')
    {
        value = value * 10 + static_cast<unsigned int>(*text - '0');
        text++;
    }

    return value;
}

static void print_number(unsigned int value)
{
    char digits[11];
    int length = 0;

    if (value == 0)
    {
        vga_putc('0');
        return;
    }

    while (value > 0)
    {
        digits[length++] = static_cast<char>('0' + value % 10);
        value /= 10;
    }

    while (length > 0)
        vga_putc(digits[--length]);
}

static void kernel_game()
{
    vga_print("\nGAME: guess a number from 1 to 100\n");
    vga_print("The target is 42. Type exit to leave.\n");

    while (true)
    {
        char input[32];
        int length = 0;
        vga_print("Guess: ");

        while (true)
        {
            char character = keyboard_getchar();

            if (!character)
                continue;

            if (character == '\n')
            {
                input[length] = 0;
                vga_print("\n");
                break;
            }

            if (character == '\b')
            {
                if (length > 0)
                {
                    --length;
                    vga_putc('\b');
                }
                continue;
            }

            if (length < 31)
            {
                input[length++] = character;
                vga_putc(character);
            }
        }

        if (equals(input, "exit"))
            return;

        unsigned int guess = number_from(input);
        if (guess == 42)
        {
            vga_print("You win!\n");
            return;
        }

        if (guess < 42)
            vga_print("Too low.\n");
        else
            vga_print("Too high.\n");
    }
}


// ========================================
// Echo command
// ========================================

static void echo_command(const char* cmd)
{
    if (cmd[0] == 0)
        return;

    if (cmd[0] != 'e' ||
        cmd[1] != 'c' ||
        cmd[2] != 'h' ||
        cmd[3] != 'o')
    {
        return;
    }

    if (cmd[4] == 0)
        return;

    if (cmd[4] == ' ')
    {
        vga_print("\n");

        vga_print(cmd + 5);
    }
}


// ========================================
// Command handler
// ========================================

static void command(const char* cmd)
{
    if (equals(cmd, "help"))
    {
        vga_print("\n");
        vga_print("AVAILABLE COMMANDS\n");
        vga_print("------------------------------\n");
        vga_print("help      Show commands\n");
        vga_print("clear     Clear terminal\n");
        vga_print("about     About EDORA OS\n");
        vga_print("echo      Echo text\n");
        vga_print("debug     Kernel diagnostics\n");
        vga_print("game      Number game\n");
        vga_print("ping      Network status\n");
        vga_print("net       NIC status and MAC\n");
        vga_print("panic     Test kernel panic handler\n");
        vga_print("fs        List kernel RAMFS files\n");
        vga_print("ps        List kernel processes\n");
        vga_print("disk      ATA PIO disk status\n");
    }

    else if (equals(cmd, "clear"))
    {
        vga_clear();

        vga_terminal_start();
    }

    else if (equals(cmd, "about"))
    {
        vga_print("\n");
        vga_print("EDORA OS 2.3\n");
        vga_print("------------------------------\n");
        vga_print("Real x86 Operating System\n");
        vga_print("Architecture : i386\n");
        vga_print("Boot         : BIOS\n");
        vga_print("CPU Mode     : Protected Mode\n");
        vga_print("Keyboard     : PS/2\n");
        vga_print("Display      : VGA 80x25\n");
        vga_print("Terminal     : EDORA VGA 3.1\n");
        vga_print("Made by      : XIAO LOUIE\n");
    }

    else if (equals(cmd, "debug"))
    {
        char vendor[13];
        system_cpu_vendor(vendor);
        vga_print("\nEDORA KERNEL DEBUG\n");
        vga_print("CPU vendor   : ");
        vga_print(vendor);
        vga_print("\n");
        vga_print("Mode         : i386 protected mode\n");
        vga_print("Display      : VGA text mode\n");
        vga_print("Keyboard     : PS/2 polling\n");
        vga_print("PIT timer    : 100 Hz configured\n");
        vga_print("RAM total    : ");
        print_number(ram_total_mb());
        vga_print(" MB\n");
        vga_print("RAM used     : ");
        print_number(ram_used_kb());
        vga_print(" KB\n");
        vga_print("RAM control  : firmware-managed, read-only\n");
        vga_print("Voltage      : hardware-managed, read-only\n");
        vga_print("Permission   : ");
        vga_print(auth_permission_name());
        vga_print("\n");
        vga_print("Network      : ");
        vga_print(rtl8139_ready() ? "RTL8139 online\n" : "driver not initialized\n");
        vga_print("Kernel state : running\n");
    }

    else if (equals(cmd, "net"))
    {
        rtl8139_print_status();
    }

    else if (equals(cmd, "panic"))
    {
        kernel_panic("panic command requested");
    }

    else if (equals(cmd, "fs"))
    {
        filesystem_list();
    }

    else if (equals(cmd, "ps"))
    {
        process_list();
    }

    else if (equals(cmd, "disk"))
    {
        ata_status();
    }

    else if (starts_with(cmd, "timer "))
    {
        unsigned int frequency = number_from(cmd + 6);
        if (frequency < 20 || frequency > 1000)
        {
            vga_print("Timer range: 20-1000 Hz\n");
        }
        else
        {
            timer_set_frequency(frequency);
            vga_print("PIT timer frequency updated.\n");
        }
    }

    else if (starts_with(cmd, "ping"))
    {
        if (cmd[4] != 0 && cmd[4] != ' ')
        {
            vga_print("Unknown command: ");
            vga_print(cmd);
            vga_print("\n");
        }
        else
        {
            vga_print("\nPING: network driver is not initialized\n");
            vga_print("NIC, ARP and ICMP support are required.\n");
        }
    }

    else if (equals(cmd, "game"))
    {
        kernel_game();
    }

    else if (cmd[0] == 'e' &&
             cmd[1] == 'c' &&
             cmd[2] == 'h' &&
             cmd[3] == 'o' &&
             cmd[4] == ' ')
    {
        vga_print("\n");
        vga_print(cmd + 5);
        vga_print("\n");
    }

    else if (cmd[0] != 0)
    {
        vga_print("\n");
        vga_print("Unknown command: ");
        vga_print(cmd);
        vga_print("\n");
    }

    vga_print("\n");

    vga_terminal_prompt();
}


// ========================================
// Kernel Main
// ========================================

extern "C" void kernel_main()
{
    vga_init();
    keyboard_init();
    ram_init();
    system_init();
    filesystem_init();
    process_init();
    paging_init();
    timer_init(100);
    rtl8139_init();
    interrupts_init();
    auth_init();

    if (!auth_login())
        kernel_panic("authentication failure");

    vga_terminal_start();
    vga_terminal_prompt();


    char command_buffer[128];

    int length = 0;


    while (true)
    {
        char c = keyboard_getchar();


        // Ignore unsupported input
        if (!c)
            continue;


        // =================================
        // Enter
        // =================================

        if (c == '\n')
        {
            command_buffer[length] = 0;

            command(command_buffer);

            length = 0;

            continue;
        }


        // =================================
        // Backspace
        // =================================

        if (c == '\b')
        {
            if (length > 0)
            {
                length--;

                vga_putc('\b');
            }

            continue;
        }


        // =================================
        // Normal character
        // =================================

        if (length < 127)
        {
            command_buffer[length] = c;

            length++;

            vga_putc(c);
        }
    }
}
