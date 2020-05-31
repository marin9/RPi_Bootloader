
void start() {
 	asm volatile("msr cpsr_c, #0xDF");
	asm volatile("ldr sp, =0x8000");
	asm volatile("bl setup");
    asm volatile("b .");
}
