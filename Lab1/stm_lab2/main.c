__asm void my_numbers(const char *src, char *dstr){
        MOV r4, #' '
cycle_loop
		LDRB r2, [r0]
		ADDS r0, r0, #1
		LDRB r3, [r0]
		TST  r3, #1
		BNE  cycle_skip
		STRB r2, [r1]
		ADDS r1, r1, #1
		STRB r3, [r1]
		ADDS r1, r1, #1
		STRB r4, [r1]
		ADDS r1, r1, #1
		
cycle_skip
		ADDS r0, r0, #2
		CMP r2, #0
		BNE cycle_loop
		BX lr
}

int main(void)

{
	const char a[] = "12 45 67 23 09 77 56 33 66 23";
	char b[30];
		my_numbers(a, b);
	

    while (1);
}
