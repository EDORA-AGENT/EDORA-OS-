bits 32

global _start

extern kernel_main

_start:
    cli

    mov esp, 0x90000

    call kernel_main

.hang:
    hlt
    jmp .hang