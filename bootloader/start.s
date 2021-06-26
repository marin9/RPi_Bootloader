.section .init
.global start
start:
	ldr sp, =stack
	bl main
	b .
