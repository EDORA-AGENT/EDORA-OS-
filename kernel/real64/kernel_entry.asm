bits 64

global _start64
extern kernel64_main

_start64:
    cli
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov rsp, 0x90000
    xor rbp, rbp
    call kernel64_main
.halt:
    hlt
    jmp .halt
