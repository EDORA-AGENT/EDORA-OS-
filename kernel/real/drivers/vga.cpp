
#include "vga.h"

// ========================================
// EDORA OS VGA Terminal 3.1
// VGA Text Mode: 80x25
// ========================================

static volatile unsigned short* VGA =
    (volatile unsigned short*)0xB8000;

static int row = 0;
static int column = 0;

static unsigned char color = 0x07;

static const int WIDTH = 80;
static const int HEIGHT = 25;


// ========================================
// Port I/O
// ========================================

static void outb(unsigned short port,
                 unsigned char value)
{
    asm volatile(
        "outb %0, %1"
        :
        : "a"(value),
          "Nd"(port)
    );
}


// ========================================
// Hardware Cursor
// ========================================

static void update_cursor()
{
    unsigned short position =
        row * WIDTH + column;

    // VGA cursor position low byte
    outb(0x3D4, 0x0F);
    outb(0x3D5, position & 0xFF);

    // VGA cursor position high byte
    outb(0x3D4, 0x0E);
    outb(0x3D5, (position >> 8) & 0xFF);
}


// ========================================
// Create VGA character
// ========================================

static unsigned short make_entry(char c)
{
    return ((unsigned short)color << 8) |
           (unsigned char)c;
}


// ========================================
// Cursor
// ========================================

void vga_set_cursor(int x, int y)
{
    if (x < 0)
        x = 0;

    if (y < 0)
        y = 0;

    if (x >= WIDTH)
        x = WIDTH - 1;

    if (y >= HEIGHT)
        y = HEIGHT - 1;

    column = x;
    row = y;

    update_cursor();
}


void vga_get_cursor(int* x, int* y)
{
    if (x)
        *x = column;

    if (y)
        *y = row;
}


// ========================================
// Color
// ========================================

void vga_set_color(unsigned char foreground,
                   unsigned char background)
{
    color =
        ((background & 0x0F) << 4) |
        (foreground & 0x0F);
}


void vga_reset_color()
{
    color = 0x07;
}


// ========================================
// Direct write
// ========================================

void vga_write_at(int x, int y, char c)
{
    if (x < 0 || x >= WIDTH)
        return;

    if (y < 0 || y >= HEIGHT)
        return;

    VGA[y * WIDTH + x] =
        make_entry(c);
}


// ========================================
// Clear screen
// ========================================

void vga_clear()
{
    unsigned char old_color = color;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            VGA[y * WIDTH + x] =
                ((unsigned short)old_color << 8) |
                ' ';
        }
    }

    row = 0;
    column = 0;

    update_cursor();
}


// ========================================
// Scroll
// ========================================

static void scroll()
{
    if (row < HEIGHT)
        return;

    for (int y = 1; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            VGA[(y - 1) * WIDTH + x] =
                VGA[y * WIDTH + x];
        }
    }

    for (int x = 0; x < WIDTH; x++)
    {
        VGA[(HEIGHT - 1) * WIDTH + x] =
            make_entry(' ');
    }

    row = HEIGHT - 1;

    update_cursor();
}


// ========================================
// Character output
// ========================================

void vga_putc(char c)
{
    // New line
    if (c == '\n')
    {
        column = 0;
        row++;

        scroll();
        update_cursor();

        return;
    }


    // Carriage return
    if (c == '\r')
    {
        column = 0;

        update_cursor();

        return;
    }


    // Backspace
    if (c == '\b')
    {
        if (column > 0)
        {
            column--;

            VGA[row * WIDTH + column] =
                make_entry(' ');
        }

        update_cursor();

        return;
    }


    // Tab
    if (c == '\t')
    {
        int spaces =
            4 - (column % 4);

        for (int i = 0; i < spaces; i++)
        {
            vga_putc(' ');
        }

        return;
    }


    // Normal character
    VGA[row * WIDTH + column] =
        make_entry(c);

    column++;

    if (column >= WIDTH)
    {
        column = 0;
        row++;
    }

    scroll();

    update_cursor();
}


// ========================================
// String output
// ========================================

void vga_print(const char* text)
{
    if (!text)
        return;

    while (*text)
    {
        vga_putc(*text);
        text++;
    }
}


// ========================================
// Horizontal line
// ========================================

static void draw_horizontal(int x1,
                            int x2,
                            int y)
{
    if (y < 0 || y >= HEIGHT)
        return;

    for (int x = x1; x <= x2; x++)
    {
        if (x >= 0 && x < WIDTH)
            vga_write_at(x, y, '-');
    }
}


// ========================================
// Vertical line
// ========================================

static void draw_vertical(int y1,
                          int y2,
                          int x)
{
    if (x < 0 || x >= WIDTH)
        return;

    for (int y = y1; y <= y2; y++)
    {
        if (y >= 0 && y < HEIGHT)
            vga_write_at(x, y, '|');
    }
}


// ========================================
// Draw box
// ========================================

void vga_draw_box(int x1,
                  int y1,
                  int x2,
                  int y2)
{
    if (x1 < 0)
        x1 = 0;

    if (y1 < 0)
        y1 = 0;

    if (x2 >= WIDTH)
        x2 = WIDTH - 1;

    if (y2 >= HEIGHT)
        y2 = HEIGHT - 1;


    vga_write_at(x1, y1, '+');
    vga_write_at(x2, y1, '+');

    vga_write_at(x1, y2, '+');
    vga_write_at(x2, y2, '+');


    draw_horizontal(
        x1 + 1,
        x2 - 1,
        y1
    );

    draw_horizontal(
        x1 + 1,
        x2 - 1,
        y2
    );

    draw_vertical(
        y1 + 1,
        y2 - 1,
        x1
    );

    draw_vertical(
        y1 + 1,
        y2 - 1,
        x2
    );
}


// ========================================
// Header
// ========================================

void vga_draw_header(const char* title)
{
    unsigned char old_color = color;

    vga_set_color(15, 1);

    for (int x = 0; x < WIDTH; x++)
    {
        vga_write_at(x, 0, ' ');
    }


    vga_set_cursor(2, 0);

    if (title)
        vga_print(title);


    const char* info = "EDORA OS";

    vga_set_cursor(
        WIDTH - 10,
        0
    );

    vga_print(info);


    color = old_color;
}


// ========================================
// Footer
// ========================================

void vga_draw_footer(const char* text)
{
    unsigned char old_color = color;

    vga_set_color(15, 1);

    for (int x = 0; x < WIDTH; x++)
    {
        vga_write_at(
            x,
            HEIGHT - 1,
            ' '
        );
    }


    vga_set_cursor(
        2,
        HEIGHT - 1
    );

    if (text)
        vga_print(text);


    color = old_color;
}


// ========================================
// Terminal startup
// ========================================

void vga_terminal_start()
{
    vga_set_color(7, 0);

    vga_clear();


    // Header
    vga_draw_header(
        " EDORA TERMINAL 3.1"
    );


    // Main border
    vga_set_color(7, 0);

    vga_draw_box(
        0,
        1,
        WIDTH - 1,
        HEIGHT - 2
    );


    // EDORA title
    vga_set_color(11, 0);

    vga_set_cursor(3, 3);

    vga_print(
        "EDORA OS"
    );


    // Description
    vga_set_color(15, 0);

    vga_set_cursor(3, 4);

    vga_print(
        "Real x86 Operating System"
    );


    // Kernel
    vga_set_color(10, 0);

    vga_set_cursor(3, 6);

    vga_print(
        "[ OK ] Kernel online"
    );


    // VGA
    vga_set_cursor(3, 7);

    vga_print(
        "[ OK ] VGA terminal initialized"
    );


    // Keyboard
    vga_set_cursor(3, 8);

    vga_print(
        "[ OK ] PS/2 keyboard ready"
    );


    // Help
    vga_set_color(14, 0);

    vga_set_cursor(3, 10);

    vga_print(
        "Type 'help' to see available commands."
    );


    // Footer
    vga_draw_footer(
        " EDORA OS 2.3 | x86 | VGA TEXT MODE "
    );


    // Shell area
    vga_set_color(15, 0);

    vga_set_cursor(3, 12);
}


// ========================================
// Shell prompt
// ========================================

void vga_terminal_prompt()
{
    vga_set_color(10, 0);

    vga_print(
        "EDORA:\\> "
    );

    vga_set_color(15, 0);
}
void vga_init()
{
    color = 0x07;
    vga_clear();
    vga_terminal_start();
}