bits 32

extern interrupt_dispatch

global interrupt_default_stub
global interrupt_timer_stub
global interrupt_keyboard_stub

interrupt_default_stub:
    pusha
    push dword 0
    call interrupt_dispatch
    add esp, 4
    popa
    iretd

interrupt_timer_stub:
    pusha
    push dword 32
    call interrupt_dispatch
    add esp, 4
    popa
    iretd

interrupt_keyboard_stub:
    pusha
    push dword 33
    call interrupt_dispatch
    add esp, 4
    popa
    iretd
