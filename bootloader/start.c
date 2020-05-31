
void _start() {
	asm volatile ("ldr sp, =0x8000");
	asm volatile ("bl main");
	asm volatile ("b .");
}
