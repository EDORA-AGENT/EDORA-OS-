#include "ata.h"
#include "vga.h"

static bool ready = false;

static void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned char inb(unsigned short port)
{
    unsigned char value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static unsigned short inw(unsigned short port)
{
    unsigned short value;
    asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static bool wait_not_busy()
{
    for (unsigned int count = 0; count < 1000000; ++count)
    {
        unsigned char status = inb(0x1F7);
        if (status == 0xFF)
            return false;
        if ((status & 0x80) == 0)
            return (status & 0x01) == 0;
    }
    return false;
}

bool ata_init()
{
    outb(0x1F6, 0xA0);
    outb(0x1F2, 0);
    outb(0x1F3, 0);
    outb(0x1F4, 0);
    outb(0x1F5, 0);
    outb(0x1F7, 0xEC);
    ready = wait_not_busy();
    return ready;
}

bool ata_ready()
{
    return ready;
}

bool ata_read_sector(unsigned int lba, unsigned char* buffer)
{
    if (!ready || !buffer)
        return false;

    if (!wait_not_busy())
        return false;

    outb(0x1F2, 1);
    outb(0x1F3, static_cast<unsigned char>(lba));
    outb(0x1F4, static_cast<unsigned char>(lba >> 8));
    outb(0x1F5, static_cast<unsigned char>(lba >> 16));
    outb(0x1F6, static_cast<unsigned char>(0xE0 | ((lba >> 24) & 0x0F)));
    outb(0x1F7, 0x20);

    unsigned char status = inb(0x1F7);
    for (unsigned int count = 0; count < 1000000; ++count)
    {
        status = inb(0x1F7);
        if (status & 0x01)
            return false;
        if ((status & 0x08) && !(status & 0x80))
            break;
    }

    for (int index = 0; index < 256; ++index)
    {
        unsigned short word = inw(0x1F0);
        buffer[index * 2] = static_cast<unsigned char>(word & 0xFF);
        buffer[index * 2 + 1] = static_cast<unsigned char>(word >> 8);
    }

    return true;
}

void ata_status()
{
    vga_print(ready ? "ATA PIO: online\n" : "ATA PIO: unavailable\n");
}
