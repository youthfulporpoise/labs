GLOBAL      _start

SECTION     .data
    prmpt1      DB      "String 1: "
    prmpt2      DB      "String 2: "
    concat      DB      "Concatenation: "
    newline     DB      0xA
    
    prmpt1_n    EQU     10
    prmpt2_n    EQU     10
    concat_n    EQU     15
    str1_n      EQU     36
    str2_n      EQU     36

SECTION     .bss
    str1    RESB    72
    str2    RESB    36

SECTION     .text
_start:
    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    prmpt1
    MOV     edx,    prmpt1_n
    INT     0x80

    MOV     eax,    3
    MOV     ebx,    0
    MOV     ecx,    str1
    MOV     edx,    str1_n
    INT     0x80
    MOV     byte [str1 + eax - 1],  0x0

    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    prmpt2
    MOV     edx,    prmpt2_n
    INT     0x80

    MOV     eax,    3
    MOV     ebx,    0
    MOV     ecx,    str2
    MOV     edx,    str2_n
    INT     0x80
    MOV     byte [str2 + eax - 1], 0x0

    MOV     esi,    str1
    MOV     edi,    str2

.string_one:
    CMP     byte [esi],  0x0
    JE      .string_two
    INC     esi
    JMP     .string_one

.string_two:
    CMP     byte [edi],  0x0
    JE      .done
    MOV     al,         [edi]
    MOV     [esi],      al
    INC     esi
    INC     edi
    JMP     .string_two

.done:

    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    concat
    MOV     edx,    concat_n
    INT     0x80

    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    str1
    MOV     edx,    str1 + str2
    INT     0x80

    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    newline
    MOV     edx,    1
    INT     0x80

    MOV     eax,    1
    MOV     ebx,    0
    INT     0x80
