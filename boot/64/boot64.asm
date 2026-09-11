bits 16
org 0x7C00

KERNEL_SEGMENT equ 0x1000
KERNEL_SECTORS equ 64

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    mov [boot_drive], dl

    mov si, boot_message
    call print_string
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb error_cpu
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 20
    jz error_nx

    mov si, dap
    mov ah, 0x42
    mov dl, [boot_drive]
    int 0x13
    jc error_disk

    call setup_page_tables
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

setup_page_tables:
    xor ax, ax
    mov es, ax
    mov di, 0x9000
    xor eax, eax
    mov cx, 4096
    rep stosd

    mov dword [0x9000], 0xA003
    mov dword [0xA000], 0xB003
    mov dword [0xB000], 0xC003

    mov edi, 0xC000
    xor eax, eax
    mov ecx, 512
.map_page:
    mov edx, eax
    or edx, 0x003
    cmp eax, 0x90000
    je .nx_page
    cmp eax, 0xB8000
    jne .write_page
.nx_page:
    mov dword [edi + 4], 0x80000000
.write_page:
    mov [edi], edx
    add eax, 0x1000
    add edi, 8
    loop .map_page
    ret

bits 32
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    mov eax, 0x9000
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, (1 << 8) | (1 << 11)
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    or eax, 1
    mov cr0, eax

    jmp 0x18:long_mode

bits 64
long_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov rsp, 0x90000
    mov rbp, rsp
    mov rax, 0x10000
    jmp rax

print_string:
.next:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp .next
.done:
    ret

error_screen:
    mov si, error_prefix
    call print_string
    call print_string
    cli
.hang:
    hlt
    jmp .hang

error_disk:
    mov si, disk_error
    jmp error_screen
error_cpu:
    mov si, cpu_error
    jmp error_screen
error_nx:
    mov si, nx_error
    jmp error_screen

boot_message db 'EDORA64 BOOT', 13, 10, 0
error_prefix db 13, 10, 'BOOT ERROR: ', 0
error_text db 'unknown', 0
disk_error db 'disk read failed', 0
cpu_error db 'x86_64 not supported', 0
nx_error db 'NX bit unavailable', 0

align 4
dap:
    db 16, 0
    dw KERNEL_SECTORS
    dw 0
    dw KERNEL_SEGMENT
    dd 1
    dd 0
boot_drive db 0

gdt_start:
    dq 0
gdt_code32:
    dq 0x00CF9A000000FFFF
gdt_data:
    dq 0x00CF92000000FFFF
gdt_code64:
    dq 0x00AF9A000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510 - ($ - $$) db 0
dw 0xAA55
