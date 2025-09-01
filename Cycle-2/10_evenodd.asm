GLOBAL        _start

SECTION       .data
  prmpt       DB        "Integer: "
  prmpt_n     EQU       9
  even        DB        "The integer is even.", 0xA
  even_n      EQU       21
  odd         DB        "The integer is odd.", 0xA
  odd_n       EQU       20
  intgr       DW        0

SECTION       .bss
  intgr_str     RESB      8
  intgr_str_n   EQU       8

SECTION       .text
_start:
  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        prmpt
  MOV       edx,        prmpt_n
  INT       0x80

  MOV       eax,        3
  MOV       ebx,        0
  MOV       ecx,        intgr_str
  MOV       edx,        intgr_str_n
  INT       0x80
  MOV       byte [intgr_str + eax - 1],   0x0

  MOV       esi,        intgr_str
  CALL      .atoi

  AND       eax,        1
  CMP       eax,        1
  JE        .is_odd
  JMP       .is_even

.is_odd:
  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        odd
  MOV       edx,        odd_n
  INT       0x80
  JMP       .exit

.is_even:
  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        even
  MOV       edx,        even_n
  INT       0x80
  JMP       .exit

.exit:
  MOV       eax,        1
  MOV       ebx,        0
  INT       0x80

; A subroutine to convert a string into an integer.
; Input:  esi -- null-ended string
; Output: eax -- converted integer
.atoi:
  MOV       eax,      0
.loop_atoi:
  IMUL      eax,            10
  MOV       bl,             byte [esi]
  SUB       bl,             '0'
  ADD       eax,            ebx
  INC       esi
  CMP       byte [esi],     0x0
  JNE       .loop_atoi
  RET
