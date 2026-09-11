#include "keyboard.h"

static unsigned char inb(unsigned short port)
{
    unsigned char value;

    asm volatile(
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
    );

    return value;
}

static bool shift = false;
static bool caps_lock = false;
static bool extended = false;
static volatile char input_buffer[128];
static volatile unsigned int input_read = 0;
static volatile unsigned int input_write = 0;

static const char normal_map[128] =
{
    0, 27,
    '1','2','3','4','5','6','7','8','9','0',
    '-','=',
    '\b','\t',
    'q','w','e','r','t','y','u','i','o','p',
    '[',']','\n',
    0,
    'a','s','d','f','g','h','j','k','l',
    ';','\'','`',
    0,
    '\\',
    'z','x','c','v','b','n','m',
    ',','.','/',
    0,
    '*',
    0,
    ' '
};

static const char shift_map[128] =
{
    0, 27,
    '!','@','#','$','%','^','&','*','(',')',
    '_','+',
    '\b','\t',
    'Q','W','E','R','T','Y','U','I','O','P',
    '{','}','\n',
    0,
    'A','S','D','F','G','H','J','K','L',
    ':','"','~',
    0,
    '|',
    'Z','X','C','V','B','N','M',
    '<','>','?',
    0,
    '*',
    0,
    ' '
};

static void enqueue(char character)
{
    unsigned int next = (input_write + 1) & 127;
    if (next == input_read)
        return;
    input_buffer[input_write] = character;
    input_write = next;
}

void keyboard_init()
{
    shift = false;
    caps_lock = false;
    extended = false;
    input_read = 0;
    input_write = 0;
}

bool keyboard_has_input()
{
    return input_read != input_write;
}

void keyboard_irq_handler()
{
    if ((inb(0x64) & 1) == 0)
        return;

    unsigned char scancode = inb(0x60);

    if (scancode == 0xE0)
    {
        extended = true;
        return;
    }

    if (scancode & 0x80)
    {
        unsigned char key = scancode & 0x7F;
        if (key == 0x2A || key == 0x36)
            shift = false;
        extended = false;
        return;
    }

    if (scancode == 0x2A || scancode == 0x36)
    {
        shift = true;
        return;
    }

    if (scancode == 0x3A)
    {
        caps_lock = !caps_lock;
        return;
    }

    if (scancode >= 128 || extended)
    {
        extended = false;
        return;
    }

    char character = shift ? shift_map[scancode] : normal_map[scancode];
    if (caps_lock && character >= 'a' && character <= 'z')
        character = character - 'a' + 'A';
    else if (caps_lock && character >= 'A' && character <= 'Z')
        character = character - 'A' + 'a';

    if (character)
        enqueue(character);
}

char keyboard_getchar()
{
    while (!keyboard_has_input())
        asm volatile("hlt");

    char character = input_buffer[input_read];
    input_read = (input_read + 1) & 127;
    return character;
}