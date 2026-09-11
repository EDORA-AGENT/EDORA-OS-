bits 32

extern exception_dispatch

global exception_divide_stub
global exception_invalid_opcode_stub
global exception_general_protection_stub
global exception_page_fault_stub

%macro exception_stub 2
%2:
    pusha
    push dword %1
    call exception_dispatch
    add esp, 4
    popa
    iretd
%endmacro

%macro exception_error_stub 2
%2:
    pusha
    push dword %1
    call exception_dispatch
    add esp, 4
    popa
    add esp, 4
    iretd
%endmacro

exception_stub 0, exception_divide_stub
exception_stub 6, exception_invalid_opcode_stub
exception_error_stub 13, exception_general_protection_stub
exception_error_stub 14, exception_page_fault_stub
