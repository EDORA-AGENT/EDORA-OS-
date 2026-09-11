#include "filesystem.h"
#include "../drivers/vga.h"

struct RamFile
{
    const char* name;
    const char* content;
};

static RamFile files[] = {
    {"/etc/login.aes", "4D025337A242CA5BFD58F78D9163F206\n"},
    {"/etc/edora.conf", "version=2.3\nmode=protected\n"},
    {"/etc/hostname", "edora\n"},
    {"/boot/kernel", "loaded\n"},
    {"/var/log/boot.log", "EDORA kernel booted\n"}
};

static unsigned int file_count = 0;

void filesystem_init()
{
    file_count = sizeof(files) / sizeof(files[0]);
}

unsigned int filesystem_file_count()
{
    return file_count;
}

void filesystem_list()
{
    vga_print("RAMFS files:\n");
    for (unsigned int index = 0; index < file_count; ++index)
    {
        vga_print("  ");
        vga_print(files[index].name);
        vga_print("\n");
    }
}
