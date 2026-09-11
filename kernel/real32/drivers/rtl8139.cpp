#include "rtl8139.h"
#include "../drivers/vga.h"

static unsigned short io_base = 0;
static bool initialized = false;
static unsigned char mac_address[6] = {};
static unsigned char receive_buffer[8192 + 16 + 1500] __attribute__((aligned(16)));
static unsigned char transmit_buffer[1536] __attribute__((aligned(4)));

static void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static void outw(unsigned short port, unsigned short value)
{
    asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}

static void outl(unsigned short port, unsigned int value)
{
    asm volatile("outl %0, %1" : : "a"(value), "Nd"(port));
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

static unsigned int inl(unsigned short port)
{
    unsigned int value;
    asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static unsigned int pci_config_read(unsigned char bus,
                                    unsigned char device,
                                    unsigned char function,
                                    unsigned char offset)
{
    unsigned int address = 0x80000000u |
        (static_cast<unsigned int>(bus) << 16) |
        (static_cast<unsigned int>(device) << 11) |
        (static_cast<unsigned int>(function) << 8) |
        (offset & 0xFC);

    outl(0xCF8, address);
    return inl(0xCFC);
}

static void pci_config_write(unsigned char bus,
                             unsigned char device,
                             unsigned char function,
                             unsigned char offset,
                             unsigned int value)
{
    unsigned int address = 0x80000000u |
        (static_cast<unsigned int>(bus) << 16) |
        (static_cast<unsigned int>(device) << 11) |
        (static_cast<unsigned int>(function) << 8) |
        (offset & 0xFC);

    outl(0xCF8, address);
    outl(0xCFC, value);
}

static bool find_card()
{
    for (unsigned int device = 0; device < 32; ++device)
    {
        unsigned int id = pci_config_read(0, static_cast<unsigned char>(device), 0, 0);
        unsigned short vendor = static_cast<unsigned short>(id & 0xFFFF);
        unsigned short device_id = static_cast<unsigned short>(id >> 16);

        if (vendor == 0x10EC && (device_id == 0x8139 || device_id == 0x8138))
        {
            unsigned int bar = pci_config_read(0, static_cast<unsigned char>(device), 0, 0x10);
            io_base = static_cast<unsigned short>(bar & 0xFFFC);

            unsigned int command = pci_config_read(0, static_cast<unsigned char>(device), 0, 0x04);
            command |= 0x00000005;
            pci_config_write(0, static_cast<unsigned char>(device), 0, 0x04, command);
            return io_base != 0;
        }
    }

    return false;
}

bool rtl8139_init()
{
    if (!find_card())
        return false;

    outb(io_base + 0x52, 0x00);
    outb(io_base + 0x37, 0x10);

    for (volatile unsigned int wait = 0; wait < 100000; ++wait)
    {
        if ((inb(io_base + 0x37) & 0x10) == 0)
            break;
    }

    outl(io_base + 0x30, reinterpret_cast<unsigned int>(receive_buffer));
    outb(io_base + 0x37, 0x0C);
    outw(io_base + 0x3C, 0x0005);
    outl(io_base + 0x44, 0x0000000F);
    outw(io_base + 0x3A, 0xFFF0);

    for (int index = 0; index < 6; ++index)
        mac_address[index] = inb(io_base + index);

    initialized = true;
    return true;
}

bool rtl8139_ready()
{
    return initialized;
}

void rtl8139_print_status()
{
    if (!initialized)
    {
        vga_print("RTL8139: not detected\n");
        return;
    }

    vga_print("RTL8139: online, polling mode\n");
    vga_print("MAC: ");

    for (int index = 0; index < 6; ++index)
    {
        const char* digits = "0123456789ABCDEF";
        vga_putc(digits[(mac_address[index] >> 4) & 0x0F]);
        vga_putc(digits[mac_address[index] & 0x0F]);
        if (index != 5)
            vga_putc(':');
    }

    vga_print("\n");
}
