GLOBAL      _start

SECTION     .data
    prmpt       DB      "String: "
    prmpt_n     EQU     8
    result      DB      "Result: "
    result_n    EQU     8
    newl        DB      0xA

SECTION     .bss
    str0        RESB    64
    str0_n      EQU     64

SECTION     .text
_start:
    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    prmpt
    MOV     edx,    prmpt_n
    INT     0x80

    MOV     eax,    3
    MOV     ebx,    0
    MOV     ecx,    str0
    MOV     edx,    str0_n
    INT     0x80
    
    MOV     byte [str0 + eax - 1],  0x0
    MOV     esi,                    str0

    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    result
    MOV     edx,    result_n
    INT     0x80

.loop:
    CMP     byte [esi],      0x0
    JE      .exit

    CALL    .uppercase
    CMP     al,             byte [esi]      ; detect change
    JNE     .next                           ; if there is change, skip
    CALL    .lowercase
    
.next:
    MOV     eax,        4
    MOV     ebx,        1
    MOV     ecx,        esi
    MOV     edx,        1
    INT     0x80

    INC     esi
    JMP     .loop

.exit:
    MOV     eax,    4
    MOV     ebx,    1
    MOV     ecx,    newl
    MOV     edx,    1
    INT     0x80

    MOV     eax,    1
    MOV     ebx,    0
    INT     0x80

.lowercase:
    MOV     al,             byte [esi]      ; for detecting change
    CMP     byte [esi],     'A'
    JL      .lc_ret
    CMP     byte [esi],     'Z'
    JG      .lc_ret
    ADD     byte [esi],     0x20
.lc_ret:
    RET

.uppercase:
    MOV     al,             byte [esi]      ; for detecting change
    CMP     byte [esi],     'a'
    JL      .uc_ret
    CMP     byte [esi],     'z'
    JG      .uc_ret
    SUB     byte [esi],     0x20
.uc_ret:
    RET
