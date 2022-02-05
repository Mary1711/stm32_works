

;X + (Y + X) + (Z - Y) + Z = Q    ;X = 26h,	Y = 06h,	Z = 09h;  44 3 47   = 94
; Q = (0x34 + !A*B*C * D)*!(A*!D*C), де A=44h, B=12h, C=13h, D=C1h.
 
 
 ; segment 1 - contants and varies
 
	AREA |MY CONSTANT|, DATA, READONLY, ALIGN =4
	
X_		DCD 0x26

Y_		DCD 0x06

Z_		DCD	0x09
	
A_		DCD 0x44

B_		DCD 0x12

C_		DCD 0x13

D_		DCD	0xC1

E_	    EQU 0x34

INVERT_	DCD 0xFFFFFFFF

 
  ; results ( changeable data )
 
	AREA |MY DATA|, DATA, READWRITE ALIGN =4
	
Q1_		DCD	0		; результат математичного виразу

Q2_	  	DCD 0   	; результат логічного виразу


   ; size and area stack
   
Stack_Size	EQU	0x00000400		; 1024 (1 kB)
	
	AREA STACK, NOINIT, READWRITE, ALIGN=4

Stack_Mem	SPACE Stack_Size

__initial_sp

 
 ; brunch of vectors

	AREA RESET, DATA, READONLY
	
    EXPORT 	__Vectors
	
    EXPORT 	Reset_Handler [WEAK]
	
__Vectors

    DCD     __initial_sp  	 ; high of stack
	
    DCD		Reset_Handler    ; reset

__Vectors_End           ; end of the vector brunch


 
    ; place of code 
   
	AREA    |.text| , CODE

    Reset_Handler PROC

	LDR	R0, =__main
	
	bx 	R0
	
	ENDP


__main PROC

	; X + (Y + X) + (Z - Y) + Z = Q    ;X = 26h,	
	; Y = 06h,	Z = 09h;
	
	; send varies and constants to registers
	
	LDR R0, = X_
	LDR	R1, [R0]
	
	LDR	R0, = Y_
	LDR	R2, [R0]
	
	LDR	R0, = Z_
	LDR	R3, [R0] 
	
	
	
	add R0, R1, R2   ; ( Y + X ) --> R4   44
	;push {R0}
	LDR	R4, [R0]
	
	  
	sub R0, R3, R2   ; ( Z - Y ) --> R5  
	;pop {R4}
	LDR	R5, [R0]
	
	
	add R0, R1, R3   ; ( X + Z ) --> R6    
	LDR	R6, [R0]
	
	
   add R0, R4, R5  ; (Y + X) + (Z - Y)     
   add R0, R0, R6  ; (Y + X) + (Z - Y) + ( X + Z) = Q 
	
	; result
	  LDR	R0, = Q1_
	 STR R0, [R0]
	
	; Q = (0x34 + !A*B*C ~ D)*!(A*!D*C), де A=44h, ; B=12h, C=13h, D=C1h.
	
	; send constants and varies to registers 
	
	LDR R0, = A_
	LDR R7, [R0]
	
	LDR R0, = B_
	LDR R8, [R0]
	
	LDR R0, = C_
	LDR R9, [R0]
	
	LDR R0, = D_
	LDR R10, [R0]
	
	LDR R0, = E_
	LDR R11, [R0]
	
	LDR R0, = INVERT_ 
	LDR R12, [R0]
	
	   ; (0x34 + !A*B*C & D)*!(A*!D*C) 
	
	EOR R0, R7, R12      ; !A
	LDR	R13, [R0]
	
	
	EOR R0, R10, R12      ; !D
	LDR	R14, [R0]
	
	
	AND R0, R8, R13      ; !AB
    AND R0, R0, R9	     ; !ABC
    LDR	R15, [R0] 
    
	AND R14, R14, R7	 ; A*!D   
	AND R14, R14, R9     ; A*!D*C
 
    EOR R14, R14, R12   ;!(A*!D*C)
	
    EOR R0, R10, R15 ; !ABC & D 
	                  
    ORR R0, R0, R11  ; 0x34 + !A*B*C & D
	
	AND R0, R0, R14  ;(0x34 + !A*B*C & D)*!(A*!D*C)
	
	
	; store the result
	LDR R0, = Q2_
	STR R0, [R0]

__mainloop
    ; place you application code here
	B __mainloop
	ENDP
		
	END
