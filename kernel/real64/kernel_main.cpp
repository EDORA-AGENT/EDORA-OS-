static void serial_out(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned char serial_in(unsigned short port)
{
    unsigned char value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static void serial_init()
{
    serial_out(0x3F9, 0x00);
    serial_out(0x3FB, 0x80);
    serial_out(0x3F8, 0x01);
    serial_out(0x3F9, 0x00);
    serial_out(0x3FB, 0x03);
}

static void serial_print(const char* text)
{
    while (*text)
    {
        while ((serial_in(0x3FD) & 0x20) == 0)
        {
        }
        serial_out(0x3F8, static_cast<unsigned char>(*text++));
    }
}

[[noreturn]] static void kernel64_panic(const char* reason)
{
    volatile unsigned short* vga = reinterpret_cast<volatile unsigned short*>(0xB8000);
    const char* title = "EDORA64 KERNEL PANIC";
    const char* prefix = "Reason: ";
    int index = 0;

    for (int cell = 0; cell < 80 * 25; ++cell)
        vga[cell] = 0x4F20;
    for (index = 0; title[index] != 0; ++index)
        vga[5 * 80 + 28 + index] = static_cast<unsigned short>(0x4F00 | title[index]);
    for (index = 0; prefix[index] != 0; ++index)
        vga[10 * 80 + 20 + index] = static_cast<unsigned short>(0x4F00 | prefix[index]);
    for (index = 0; reason[index] != 0; ++index)
        vga[10 * 80 + 28 + index] = static_cast<unsigned short>(0x4F00 | reason[index]);

    serial_print("EDORA64 PANIC: ");
    serial_print(reason);
    serial_print("\r\n");
    asm volatile("cli");
    while (true)
        asm volatile("hlt");
}

extern "C" void kernel64_main()
{
    serial_init();
    serial_print("EDORA64: kernel entry\r\n");

    unsigned int efer_low;
    unsigned int efer_high;
    asm volatile("rdmsr" : "=a"(efer_low), "=d"(efer_high) : "c"(0xC0000080));
    if ((efer_low & (1u << 11)) == 0)
        kernel64_panic("EFER.NXE is disabled");

    volatile unsigned short* vga = reinterpret_cast<volatile unsigned short*>(0xB8000);
    const char* title = "EDORA OS 64-BIT - MADE BY XIAO LOUIE";
    const char* info = "4-level paging: PML4 -> PDPT -> PD -> PT";
    const char* nx = "NXE: ENABLED | stack/VGA NX pages active";
    const char* ready = "Kernel boot completed successfully";

    for (int cell = 0; cell < 80 * 25; ++cell)
        vga[cell] = 0x1F20;
    for (int index = 0; title[index] != 0; ++index)
        vga[2 * 80 + 20 + index] = static_cast<unsigned short>(0x1F00 | title[index]);
    for (int index = 0; info[index] != 0; ++index)
        vga[6 * 80 + 16 + index] = static_cast<unsigned short>(0x1E00 | info[index]);
    for (int index = 0; nx[index] != 0; ++index)
        vga[8 * 80 + 18 + index] = static_cast<unsigned short>(0x1A00 | nx[index]);
    for (int index = 0; ready[index] != 0; ++index)
        vga[12 * 80 + 24 + index] = static_cast<unsigned short>(0x1F00 | ready[index]);

    serial_print("EDORA64: EFER.NXE enabled\r\n");
    serial_print("EDORA64: 4-level paging active\r\n");
    serial_print("EDORA64: boot completed\r\n");

    while (true)
        asm volatile("hlt");
}
