GLOBAL      _start

SECTION     .data
    prmpt       DB      "String: "
    prmpt_n     EQU     8
    yes         DB      "The string is a palindrome.", 0xA
    no          DB      "The string is not a palindrome.", 0xA
    yes_n       EQU     28
    no_n        EQU     32
    str1_n       EQU     64

SECTION     .bss
    str1         RESB    64

SECTION     .text
_start:
    MOV     byte [str1],      0x0

    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        prmpt
    MOV     edx,        prmpt_n
    INT     0x80

    MOV     eax,        3
    MOV     ebx,        0
    MOV     ecx,        str1 + 1
    MOV     edx,        str1_n - 1
    INT     0x80

    MOV     byte [str1 + eax],   0x0

    MOV     esi,        str1 + 1
    ADD     eax,        str1 - 1        ; because newline is read too
    MOV     edi,        eax

.loop:
    MOV     al,         [esi]
    CMP     al,         0x0
    JE      .is_palindrome

    MOV     bl,         [edi]
    CMP     bl,         0x0
    JE      .is_palindrome

    MOV     edx,        1
    CMP     al,         bl
    JE      .continue

    SUB     al,         0x20
    CMP     al,         bl
    JE      .continue

    ADD     al,         0x20
    SUB     bl,         0x20
    CMP     al,         bl
    JE      .continue

    JMP     .is_not_palindrome

.continue:
    INC     esi
    DEC     edi
    JMP     .loop

.is_not_palindrome:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        no
    MOV     edx,        no_n
    INT     0x80
    JMP     .done

.is_palindrome:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        yes
    MOV     edx,        yes_n
    INT     0x80

.done:
    MOV     eax,        1
    MOV     ebx,        0
    INT     0x80
