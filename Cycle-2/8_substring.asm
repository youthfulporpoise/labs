GLOBAL      _start
SECTION     .data
    prmpt1          DB      "String: "
    prmpt1_n        EQU     8
    prmpt2          DB      "Substring: "
    prmpt2_n        EQU     11
    yes             DB      "Substrings found.", 0xA
    yes_n           EQU     18
    no              DB      "No substrings found.", 0xA
    no_n            EQU     21

SECTION     .bss
    str1            RESB    36
    str2            RESB    36
    str_n           EQU     36

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
    MOV     edx,    str_n
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
    MOV     edx,    str_n
    INT     0x80
    MOV     byte [str2 + eax - 1],  0x0

    MOV     esi,    str1
    MOV     edi,    str2

.loop:
    MOV     al,             [edi]
    CMP     [esi],          al
    JNE     .skip

    INC     edi
    CMP     byte [edi],     0x0
    JE      .is_equal
    JMP     .next

.skip:
    MOV     edi,            str2

.next:
    INC     esi
    CMP     byte [esi],      0x0
    JE      .is_not_equal
    JMP     .loop

.is_equal:
   MOV      eax,        4 
   MOV      ebx,        1
   MOV      ecx,        yes
   MOV      edx,        yes_n
   INT      0x80
   JMP      .exit

.is_not_equal:
   MOV      eax,        4 
   MOV      ebx,        1
   MOV      ecx,        no
   MOV      edx,        no_n
   INT      0x80
   JMP      .exit

.exit:
    MOV     eax,        1
    MOV     ebx,        0
    INT     0x80
