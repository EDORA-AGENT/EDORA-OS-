bits 16
org 0x7C00

; =========================================================
; EDORA OS 2.0
; BIOS Bootloader
; =========================================================

KERNEL_LOAD_SEG equ 0x1000
KERNEL_SECTORS  equ 10


; =========================================================
; Boot Entry
; =========================================================

start:
    cli

    ; -------------------------
    ; Setup real-mode segments
    ; -------------------------

    xor ax, ax

    mov ds, ax
    mov es, ax
    mov ss, ax

    mov sp, 0x7C00

    ; Save BIOS boot drive
    mov [boot_drive], dl


    ; =====================================================
    ; Boot Message
    ; =====================================================

    mov si, message
    call print_string


    ; =====================================================
    ; Check BIOS INT 13h Extensions
    ; =====================================================

    mov ah, 41h
    mov bx, 55AAh
    mov dl, [boot_drive]

    int 13h

    jc disk_error

    cmp bx, 0xAA55
    jne disk_error

    test cx, 0001h
    jz disk_error


    ; =====================================================
    ; Load Kernel Using LBA
    ; =====================================================

    mov si, dap

    mov ah, 42h
    mov dl, [boot_drive]

    int 13h

    jc disk_error


    ; Kernel loaded successfully

    mov si, loaded_message
    call print_string


    ; =====================================================
    ; Enable A20
    ; =====================================================

    in al, 92h
    or al, 02h
    out 92h, al


    ; =====================================================
    ; GDT
    ; =====================================================

    mov si, gdt_message
    call print_string

    cli

    lgdt [gdt_descriptor]


    ; =====================================================
    ; Protected Mode Message
    ; =====================================================

    mov si, pm_message
    call print_string


    ; =====================================================
    ; Enable Protected Mode
    ; =====================================================

    mov eax, cr0
    or eax, 1
    mov cr0, eax


    ; =====================================================
    ; Far Jump
    ; =====================================================

    jmp 08h:protected_mode


; =========================================================
; 32-bit Protected Mode
; =========================================================

bits 32

protected_mode:

    ; =====================================================
    ; VGA Debug
    ; =====================================================

    mov edi, 0xB8000

    mov byte [edi + 0], 'P'
    mov byte [edi + 1], 0x0F

    mov byte [edi + 2], 'M'
    mov byte [edi + 3], 0x0F

    mov byte [edi + 4], '!'
    mov byte [edi + 5], 0x0F


    ; =====================================================
    ; Load Data Segments
    ; =====================================================

    mov ax, 0x10

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax


    ; =====================================================
    ; Kernel Stack
    ; =====================================================

    mov esp, 0x90000


    ; =====================================================
    ; Jump to Kernel
    ;
    ; Kernel physical address:
    ; 0x10000
    ; =====================================================

    db 0xEA
    dd 0x10000
    dw 0x08


; =========================================================
; Kernel / Boot Hang
; =========================================================

hang:
    cli

.halt:
    hlt
    jmp .halt


; =========================================================
; 16-bit BIOS Functions
; =========================================================

bits 16


; =========================================================
; Print String
; =========================================================

print_string:

.next:
    lodsb

    test al, al
    jz .done

    mov ah, 0Eh
    mov bh, 00h

    int 10h

    jmp .next

.done:
    ret


; =========================================================
; Disk Error
; =========================================================

disk_error:

    ; Save BIOS error code
    mov [disk_error_code], ah

    mov si, error_message
    call print_string

    mov si, error_code_message
    call print_string

    mov al, [disk_error_code]
    call print_hex

    cli

.error_hang:
    hlt
    jmp .error_hang


; =========================================================
; Print 8-bit Hexadecimal
; =========================================================

print_hex:

    push ax
    push bx

    mov bl, al

    ; High nibble
    shr al, 4
    call print_hex_digit

    ; Low nibble
    mov al, bl
    and al, 0Fh
    call print_hex_digit

    pop bx
    pop ax

    ret


; =========================================================
; Print Hex Digit
; =========================================================

print_hex_digit:

    cmp al, 9
    jbe .number

    add al, 'A' - 10
    jmp .print

.number:

    add al, '0'

.print:

    mov ah, 0Eh
    mov bh, 00h

    int 10h

    ret


; =========================================================
; Global Descriptor Table
; =========================================================

align 8

gdt_start:


; ---------------------------------------------------------
; Null Descriptor
; ---------------------------------------------------------

gdt_null:
    dq 0


; ---------------------------------------------------------
; Code Segment
; Selector = 0x08
; ---------------------------------------------------------

gdt_code:

    dw 0FFFFh
    dw 0000h
    db 00h
    db 10011010b
    db 11001111b
    db 00h


; ---------------------------------------------------------
; Data Segment
; Selector = 0x10
; ---------------------------------------------------------

gdt_data:

    dw 0FFFFh
    dw 0000h
    db 00h
    db 10010010b
    db 11001111b
    db 00h


gdt_end:


; =========================================================
; GDT Descriptor
; =========================================================

gdt_descriptor:

    dw gdt_end - gdt_start - 1
    dd gdt_start


; =========================================================
; BIOS Disk Address Packet
; =========================================================

align 4

dap:

    ; Size of DAP
    db 16

    ; Reserved
    db 0

    ; Number of sectors
    dw KERNEL_SECTORS

    ; Destination offset
    dw 0x0000

    ; Destination segment
    dw KERNEL_LOAD_SEG

    ; Starting LBA
    dd 1

    ; High 32 bits of LBA
    dd 0


; =========================================================
; Boot Data
; =========================================================

boot_drive:
    db 0

disk_error_code:
    db 0


; =========================================================
; Messages
; =========================================================

message:

    db "EDORA OS 2.0 BOOTLOADER"
    db 13, 10, 0


loaded_message:

    db "KERNEL LOADED"
    db 13, 10, 0


gdt_message:

    db "GDT OK"
    db 13, 10, 0


pm_message:

    db "ENTERING PM"
    db 13, 10, 0


error_message:

    db "DISK ERROR"
    db 13, 10, 0


error_code_message:

    db " BIOS="
    db 0


; =========================================================
; Boot Sector Padding
; =========================================================

times 510 - ($ - $$) db 0


; =========================================================
; Boot Signature
; =========================================================

dw 0xAA55