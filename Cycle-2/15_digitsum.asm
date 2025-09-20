GLOBAL        _start

SECTION       .data
  prmpt     DB      "Integer: "
  prmpt_n   EQU     9
  result    DB      "Sum: "
  result_n  EQU     5
  newl      DB      0xA

SECTION       .bss
  str1      RESB    32
  str1_n    EQU     32
  count     RESW    1

SECTION       .text
_start:
  MOV     eax,      4
  MOV     ebx,      1
  MOV     ecx,      prmpt
  MOV     edx,      prmpt_n
  INT     0x80

  MOV     eax,      3
  MOV     ebx,      0
  MOV     ecx,      str1
  MOV     edx,      str1_n
  INT     0x80
  MOV     byte [str1 + eax - 1],  0x0

  MOV     esi,      str1
  MOV     eax,      0

.loop:
  CMP     byte [esi],   '0'
  JL      .exit
  CMP     byte [esi],   '9'
  JG      .exit

  ADD     al,      byte [esi]
  SUB     eax,      '0'
  INC     esi
  JMP     .loop

.exit:
  MOV     [count],  eax

  MOV     eax,      4
  MOV     ebx,      1
  MOV     ecx,      result
  MOV     edx,      result_n
  INT     0x80

  MOV      ax,      [count]
  MOV     esi,      str1
  CALL    .itoa
  MOV     esi,      str1
  CALL    .print_reverse

  MOV     eax,      1
  MOV     ebx,      0
  INT     0x80

; In:    ax -- integer                (req.)
; Out:  esi -- destination string     (req.)
.itoa:
  MOV       ebx,             10

.loop_itoa:
  XOR       edx,             edx
  DIV       ebx

  ADD       edx,            '0'
  MOV       [esi],          edx

  INC       esi
  CMP       eax,             0
  JNE       .loop_itoa
  MOV       byte [esi],     0x0
  RET

; In:   esi -- string
.print_reverse:
  PUSH      0x0

.push_loop:
  CMP       byte [esi],     0x0
  JE        .pop_loop
  PUSH      esi
  INC       esi
  JMP       .push_loop

.pop_loop:
  POP       esi
  CMP       esi,            0x0
  JE        .print_reverse_ret
    
  MOV       eax,            4
  MOV       ebx,            1
  MOV       ecx,            esi
  MOV       edx,            1
  INT       0x80

  JMP       .pop_loop

.print_reverse_ret:
  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      newl
  MOV         edx,      1
  INT         0x80

  RET
