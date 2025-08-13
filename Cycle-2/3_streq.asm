global _start

SECTION     .data
    str1prmpt   DB      "String 1: "
    str2prmpt   DB      "String 2: "
    yes         DB      "The strings are equal.", 0xA
    no          DB      "The strings are not equal.", 0xA
    str_n       EQU     36
    yes_n       EQU     23
    no_n        EQU     27

SECTION     .bss
    str1        RESB    str_n
    str2        RESB    str_n
    str1_n      RESW    1
  ; str2_n will be available in eax (vide l.47)

SECTION     .text
_start:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        str1prmpt
    MOV     edx,        10
    INT     0x80

    MOV     eax,        3
    MOV     ebx,        0
    MOV     ecx,        str1
    MOV     edx,        str_n 
    INT     0x80
    MOV     byte [str1 + eax - 1],  0
    MOV     [str1_n],   eax

    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        str2prmpt
    MOV     edx,        10
    INT     0x80

    MOV     eax,        3
    MOV     ebx,        0
    MOV     ecx,        str2
    MOV     edx,        str_n
    INT     0x80
    MOV     byte [str1 + eax - 1],  0

    CMP     [str1_n],   eax
    JNE     .notequal

    MOV     esi,        str1
    MOV     edi,        str2

.loop:
    CMP     byte [esi], 0x0
    JE      .equal
    CMP     byte [edi], 0x0
    JE      .equal

    MOV     al,         [edi]
    CMP     byte [esi], al
    JNE     .notequal
    INC     esi
    INC     edi
    JMP     .loop

.notequal:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        no
    MOV     edx,        no_n
    INT     0x80
    JMP     .done

.equal:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        yes
    MOV     edx,        yes_n
    INT     0x80

.done:
    MOV     eax,    1       ; kernel opcode for SYS_EXIT
    MOV     ebx,    0       ; exit code
    INT     0x80
