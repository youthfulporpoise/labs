global        _start

SECTION       .data
  prmpt       DB        "A = "
  prmpt_n     EQU       4
  result      DB        "A! = "
  result_n    EQU       5
  newl        DB        0xA

SECTION       .bss
  fact        RESB      32
  intgr       RESW      1
  str1        RESB      32
  str1_n      EQU       32

SECTION       .text
_start:
  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      prmpt
  MOV         edx,      prmpt_n
  INT         0x80

  MOV         eax,      3
  MOV         ebx,      0
  MOV         ecx,      str1
  MOV         edx,      str1_n
  INT         0x80
  MOV         byte [str1 + eax - 1],  0x0

  MOV         esi,      str1
  CALL        .atoi
  MOV         [intgr],  eax

  MOV         eax,      4
  MOV         ebx,      1
  MOV         ecx,      result
  MOV         edx,      result_n
  INT         0x80

; here we find the factorial
  MOV         ecx,      [intgr]
  MOV         ebx,      0
  MOV         eax,      1
.factorial:
  INC         ebx
  IMUL        eax,      ebx
  CMP         ebx,      ecx
  JNE         .factorial

  MOV         esi,      fact
  CALL        .itoa
  MOV         esi,      fact
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
