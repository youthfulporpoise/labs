GLOBAL      _start

SECTION     .data
    prmpt       DB      "String: "
    prmpt_n     EQU     8
    result      DB      "Result: "
    result_n    EQU     8
    newl        DB      0xA

SECTION     .bss
    str0         RESB    64
    str0_n      EQU     64

SECTION     .text
_start:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        prmpt
    MOV     edx,        prmpt_n
    INT 0x80

    MOV     eax,        3
    MOV     ebx,        0
    MOV     ecx,        str0
    MOV     edx,        str0_n
    INT     0x80

    SUB     eax,                1
    MOV     byte [str0 + eax],  0x0

    MOV     esi,        str0
    PUSH    0x0

.push_loop:
    CMP     byte [esi], 0x0
    JE      .print
    PUSH    esi
    INC     esi
    JMP     .push_loop

.print:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        result
    MOV     edx,        result_n
    INT     0x80

.pop_loop:
    POP     esi
    CMP     esi,        0x0
    JE      .exit

    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        esi
    MOV     edx,        1
    INT     0x80

    JMP     .pop_loop

.exit:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        newl
    MOV     edx,        1
    INT     0x80

    MOV     eax,        1
    MOV     ebx,        0
    INT     0x80
