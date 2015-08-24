
;<Program title>

jmp start

;data


;code
start: nop
lda 90h
cpi 1h
jz adn8
cpi 2h
jz subt8
cpi 3h
jz mul8
cpi 4h
jz div8
cpi 5h
jz adn16
cpi 6h
jz subt16
cpi 7h
jz mul16
cpi 8h
jz div16
cpi 9h
jz squ
cpi 0ah
jz sqroot
cpi 0bh
jz fact
cpi 0ch
jz cubed
cpi 0dh
jz sin
cpi 0eh
jz cos
cpi 0fh
jz log
hlt
;lxi 4201h;lda m;lxi 4202h;mov d,m 
adn8: call addition8
hlt
subt8: call subtraction8
hlt
mul8: call multiplication8
hlt
div8: call division8
hlt
adn16: call addition16
hlt
subt16: call subtraction16
hlt
mul16: call multiplication16
hlt
div16: call division16
hlt
squ: call square
hlt
sqroot: call squareroot
hlt
fact: call factorial
hlt
cubed: call subcube
hlt
sin: call subsine
hlt
cos: call subcos
hlt
log: call sublog
hlt
hlt
;addition of two 8 bit numbers
addition8: MVI D,00h
LDA 4200h
MOV B,A
LDA 4201h
ADD B
JNC LABEL1
INR D
LABEL1: STA 4202h
MOV A,D
STA 4203h
RET
;subtraction of two 8 bit numbers
subtraction8: MVI C,00 ;I Initialize C to 00
          LDA 4150h    ;Load the value to Acc.
          MOV B,A    ;Move the content of Acc to B register.
          LDA 4151h    ;Load the value to Acc.
          SUB B
          JNC LOOP    ;Jump on no carry.
          CMA         ;Complement Accumulator contents.
          INR A       ;Increment value in Accumulator.
          INR C       ;Increment value in register C

LOOP:     STA 4152h   ;Store the value of A-reg to memory address.
          MOV A,C   ;Move contents of register C to Accumulator.
          STA 4153h   ;Store the value of Accumulator memory address.
          RET        ;return the program.
;subtraction of two 16 bit numbers
subtraction16: LHLD 400h               
XCHG                        
LHLD 402h              
MOV A,E                   
SUB L                     
MOV L,A                   
MOV A,D                   
SBB H                     
MOV H,A                   
SHLD 404h	
RET
;multiplication of two 8 bit numbers
multiplication8: LDA 8000h
	  MOV B,A
	  LDA 8001h
	  MOV D,A
	  CALL multiply8
	  STA 8002h
	  MOV A,C
	  STA 8003h
	  ret
multiply8:	MVI A,00H
	 	MVI C,00H
noZERO:	 	ADD B
	 	JNC noCARRY
	 	INR C
noCARRY: 	DCR D
	 	JNZ noZERO
		RET
;division of two 8 bit numbers
division8: MVI C,00h
LDA 4200h
MOV B,A
LDA 4201h
LABEL: SBB B
INR C
JNC LABEL
DCR C
ADD B
STA 4202h
MOV A,C
STA 4203h
RET
;addition of two 16 bit numbers
addition16: LHLD 4000H     ;Get first I6-bit number in HL
XCHG                        ; Save first I6-bit number in DE
LHLD 4002H                ; Get second I6-bit number in HL
MOV A,E                ; Get lower byte of the first number
ADD L                        ; Add lower byte of the second number
MOV L,A                ; Store result in L register
MOV A,D                ; Get higher byte of the first number
ADC H                        ; Add higher byte of the second number with CARRY
MOV H,A                ; Store result in H register
SHLD 4004H                ; Store I6-bit result in memory locations 4004H and
RET 
;multiplication of two 16 bit numbers
multiplication16: LXI B, 0000H
	LHLD 8000H
	XCHG
	LHLD 8002H
	DCX D
L006:	LDA 8002H
	ADD L
	MOV L,A
	LDA 8003H
	ADC H
	MOV H,A
	JNC L013
	INX B
	DCX D

L013:	MOV A,D
	ORA E
	JNZ L006
	SHLD 8006H
	MOV L,C
	MOV H,B
	SHLD 8004H
	RET
;division of two 16 bit numbers
division16: lhld 4052h
	xchg
	lhld 4050h
	lxi b,0000h
loop:  mov a,l
	sub e
	mov l,a
	mov a,h
	sbb d
	mov h,a
	inx b
	jnc loop
	dcx b
	dad d
	shld 4054h
	mov a,c
	sta 4056h
	mov a,b
	sta 4057h
	ret
square:   LDA 208h
	  MOV B,A
	  MOV D,A
	  CALL multi8
	  STA 20ah
	  MOV A,C
	  STA 20bh
	 ret
multi8:	MVI A,00H
	 	MVI C,00H
noZEROs:	 	ADD B
	 	JNC noCARRYs
	 	INR C
noCARRYs: 	DCR D
	 	JNZ noZEROs
		ret
squareroot: MVI C,01h
MVI E,01h
LDA 7000h
LBL: SBB C      
JZ LBL1
INR C
INR C
INR E
JMP LBL
LBL1: MOV A,E
STA 7002h
ret
factorial: lda 8000h
mov b, a
MOV C, b
DCR C
LABEL21: MOV E, C
SUB A
LABEL11: ADD B
DCR E
JNZ LABEL11
MOV B, A
DCR C
JNZ LABEL21
STA 8002H
ret
subcube: LDA 7000H 
MVI B,02H 
MOV C,A 
MOV D,A 
L2: MVI A,00H 
L1: ADD D 
DCR C 
JNZ L1 
MOV C,A 
DCR B 
JNZ L2 
MOV A,C 
STA 7001H 
HLT 
subsine: hlt
subcos: hlt
sublog: hlt