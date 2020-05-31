.global start
start:
 	msr cpsr_c, #0xDF
	ldr sp, =start
	bl setup
	b .
