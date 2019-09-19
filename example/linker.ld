ENTRY(_start)

SECTIONS{
	. = 0x10000;
	
	__start = .;

	.text : {
		start.o(.text*);
		*(.text*);
	}

	.data : {
		*(.rodata*);
		*(.data*);
	}

	.bss : {
		*(.bss*);
	}

	__end = .;
}

