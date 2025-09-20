GLOBAL        _start

SECTION       .data
  prmpt1      DB        "A = "
  prmpt2      DB        "B = "
  prmpt_n     EQU       4
  result      DB        "gcd(A, B) = "
  result_n    EQU       12
  gcd         DW        0
  newl        DB        0xA

SECTION       .bss
  str1        RESB      16
  str2        RESB      16
  int_1       RESW      1
  int_2       RESW      1
  str_n       EQU       16

SECTION       .text
_start:
  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        prmpt1
  MOV       edx,        prmpt_n
  INT       0x80

  MOV       eax,        3
  MOV       ebx,        0
  MOV       ecx,        str1
  MOV       edx,        str_n
  INT       0x80
  MOV       byte [str1 + eax - 1],  0x0

  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        prmpt2
  MOV       edx,        prmpt_n
  INT       0x80
  
  MOV       eax,        3
  MOV       ebx,        0
  MOV       ecx,        str2
  MOV       edx,        str_n
  INT       0x80
  MOV       byte  [str2 + eax - 1], 0x0

  MOV       esi,        str1
  CALL      .atoi
  MOV       [int_1],    eax

  MOV       esi,        str2
  CALL      .atoi
  MOV       [int_2],    eax

  CALL      .gcd
  MOV       [int_1],    eax

  MOV       eax,        4
  MOV       ebx,        1
  MOV       ecx,        result
  MOV       edx,        result_n
  INT       0x80

  MOV       eax,        [int_1]
  MOV       esi,        str1
  CALL      .itoa
  MOV       esi,        str1
  CALL      .print_reverse

  MOV       eax,        1
  MOV       ebx,        0
  INT       0x80

; In:   int_1 -- A
;       int_2 -- B
; Out:  eax -- gcd(A, B)
.gcd:
  CMP   word [int_2],   0
  JE    .gcd_ret

  XOR   edx,      edx
  MOV   eax,      [int_1]
  MOV   ebx,      [int_2]
  DIV   ebx

  MOV   [int_1],  ebx
  MOV   [int_2],  edx

  MOV   eax,      [int_1]
  JMP   .gcd
  
.gcd_ret:
  RET

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
