global      _start

section        .data
msg1        DB          "String: ", 0xa
msg2        DB          " count: "
newline     DB          0xa

section        .bss
str1        resb        96
count       resb        1

section         .text
_start:
    ; print prompt
    MOV     eax,        4                       ; kernel opcode for SYS_WRITE
    MOV     ebx,        1                       ; stdout
    MOV     ecx,        msg1
    MOV     edx,        8                       ; msg1 length
    INT     0x80

    ; read string
    MOV     eax,        3                       ; kernel opcode for SYS_READ
    MOV     ebx,        0                       ; stdin
    MOV     ecx,        str1
    MOV     edx,        100
    INT     0x80
    MOV     byte [str1 + eax - 1],      0       ; o/p written to eax, null appended

    ; SYS_READ stores into eax the number of character read plus one
    ; because newline by return is also read.  The index of null would
    ; therefore have to be (i - 1).

    ; initialize
    MOV     edi,        str1

.loop1:
    MOV     esi,        str1                    ; reset esi
    MOV     al,         byte [edi]              ; load c0
    MOV     ecx,        0                       ; set count to zero
    CMP     al,         0                       ; check for EOL
    JE      .exit

.loop2:
    MOV     dl,         byte [esi]              ; load c1
    CMP     dl,         0                       ; check for EOL
    JE      .next
    CMP     al,         dl
    JNE     .skip
    INC     ecx

.skip:
    INC     esi
    JMP     .loop2

.next:
    ; ready count for print
    MOV     ebx,            ecx
    ADD     bl,             '0'                     ; convert to ASCII
    MOV     [count],        bl

    ; print letter
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        edi
    MOV     edx,        1
    INT     0x80
    
    ; print count prompt
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        msg2
    MOV     edx,        8
    INT     0x80
    
    ; print count
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        count
    MOV     edx,        1
    INT     0x80

    ; print newline
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        newline
    INT     0x80

    INC     edi
    JMP     .loop1

.exit:
    MOV     eax,        1                       ; kernel opcode for SYS_EXIT
    MOV     ebx,        0
    INT     0x80
