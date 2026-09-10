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

void keyboard_init()
{
    shift = false;
    caps_lock = false;
    extended = false;
}

bool keyboard_has_input()
{
    return (inb(0x64) & 1) != 0;
}

char keyboard_getchar()
{
    while (!keyboard_has_input())
    {
    }

    unsigned char scancode = inb(0x60);

    if (scancode == 0xE0)
    {
        extended = true;
        return 0;
    }

    if (scancode & 0x80)
    {
        unsigned char key = scancode & 0x7F;

        if (key == 0x2A || key == 0x36)
            shift = false;

        extended = false;

        return 0;
    }

    if (scancode == 0x2A || scancode == 0x36)
    {
        shift = true;
        return 0;
    }

    if (scancode == 0x3A)
    {
        caps_lock = !caps_lock;
        return 0;
    }

    if (scancode >= 128)
        return 0;

    if (extended)
    {
        extended = false;
        return 0;
    }

    char c;

    if (shift)
        c = shift_map[scancode];
    else
        c = normal_map[scancode];

    if (caps_lock && c >= 'a' && c <= 'z')
    {
        if (!shift)
            c = c - 'a' + 'A';
    }

    if (caps_lock && shift && c >= 'A' && c <= 'Z')
    {
        c = c - 'A' + 'a';
    }

    return c;
}