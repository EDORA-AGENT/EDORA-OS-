
#include "drivers/keyboard.h"
#include "drivers/vga.h"


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


    // Cursor starts after the welcome screen
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
