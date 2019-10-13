.global _start
_start:

	ldr sp, =0x8000
	bl main
	b .

