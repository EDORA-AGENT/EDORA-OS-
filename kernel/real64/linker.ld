ENTRY(_start64)
SECTIONS
{
    . = 0x10000;
    .text : { *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(COMMON) *(.bss*) }
}
