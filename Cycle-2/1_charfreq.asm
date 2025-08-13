global      _start

section        .data
msg1        db          "String: ", 0xa
msg2        db          "Character: ", 0xa
newline     db          0xa

section        .bss
str1        resb        100
chr         resb        1
count       resb        1

section         .text
_start:
    ; print prompt
    mov     eax,        4                       ; kernel opcode for SYS_WRITE
    mov     ebx,        1                       ; stdout
    mov     ecx,        msg1
    mov     edx,        9                       ; msg1 length
    int     0x80

    ; read string
    mov     eax,        3                       ; kernel opcode for SYS_READ
    mov     ebx,        0                       ; stdin
    mov     ecx,        str1
    mov     edx,        100
    int     0x80
    mov     byte        [str1 + eax + 1], 0

    ; print character
    mov     eax,        4
    mov     ebx,        1
    mov     ecx,        msg2
    mov     edx,        12
    int     0x80

    ; read character
    mov     eax,        3
    mov     ebx,        0
    mov     ecx,        chr
    mov     edx,        1
    int     0x80

    ; initialize
    mov     esi,        str1
    mov     dl,         [chr]
    mov     ecx,        0

.loop1:
    mov     al,         [esi]
    cmp     al,         0
    je      .done
    cmp     al,         dl
    jne     .skip
    inc     ecx

.skip:
    inc     esi
    jmp     .loop1

.done:
    mov     eax,        ecx
    add     eax,        '0'
    mov     [count],    al
    
    ; print count
    mov     eax,        4
    mov     ebx,        1
    mov     ecx,        count
    mov     edx,        1
    int     0x80

    ; print newline
    mov     ecx,        newline
    int     0x80

    ; exit
    mov     eax,        1                       ; kernel opcode for SYS_EXIT
    mov     ebx,        0
    int     0x80
