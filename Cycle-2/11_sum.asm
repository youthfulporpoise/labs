global        _start

SECTION       .data
  prmpt1      DB        "A = "
  prmpt1_n    EQU       4
  prmpt2      DB        "B = "
  prmpt2_n    EQU       4
  result1     DB        "A + B = "
  result1_n   EQU       8
  result2     DB        "A - B = "
  result2_n   EQU       8
  newl        DB        0xA

SECTION       .bss
  sum         RESB      32
  diff        RESW      32
  intgr1      RESW      1
  intgr2      RESW      1
  str1        RESB      32
  str1_n      EQU       32
  str2        RESB      32
  str2_n      EQU       32

SECTION       .text
_start:
  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      prmpt1
  MOV         edx,      prmpt1_n
  INT         0x80

  MOV         eax,      3
  MOV         ebx,      0
  MOV         ecx,      str1
  MOV         edx,      str1_n
  INT         0x80
  MOV         byte [str1 + eax - 1],  0x0

  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      prmpt2
  MOV         edx,      prmpt2_n
  INT         0x80

  MOV         eax,      3
  MOV         ebx,      0
  MOV         ecx,      str2
  MOV         edx,      str2_n
  INT         0x80
  MOV         byte [str2 + eax - 1],  0x0

  MOV         esi,      str1
  CALL        .atoi
  MOV         [intgr1], eax

  MOV         esi,      str2
  CALL        .atoi
  MOV         [intgr2], eax

  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      result1
  MOV         edx,      result1_n
  INT         0x80

  MOV         eax,      [intgr1]
  ADD         eax,      [intgr2]
  MOV         esi,      sum
  CALL        .itoa
  MOV         esi,      sum
  CALL        .print_reverse

  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      result2
  MOV         edx,      result2_n
  INT         0x80

  MOV         eax,      [intgr1]
  SUB         eax,      [intgr2]
  MOV         esi,      diff
  CALL        .itoa
  MOV         esi,      diff
  CALL        .print_reverse

  MOV         eax,      1
  MOV         ebx,      0
  INT         0x80

; In:   esi -- null-appended string   (req.)
; Out:  eax -- converted integer
.atoi:
  MOV       eax,        0

.loop_atoi:
  IMUL      eax,          10
  MOV       bl,           byte [esi]
  SUB       bl,           '0'
  ADD       eax,          ebx

  INC       esi
  CMP       byte [esi],   0x0
  JNE       .loop_atoi
  RET

; In:    ax -- integer                (req.)
; Out:  esi -- destination string     (req.)
.itoa:
  MOV       bl,             10

.loop_itoa:
  XOR       ah,             ah
  DIV       bl

  ADD       ah,             '0'
  MOV       [esi],          ah

  INC       esi
  CMP       al,             0
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
