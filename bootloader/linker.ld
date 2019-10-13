ENTRY(_start)

SECTIONS{
	. = 0x8000;
	
	__start = .;

	.text : {
		start.o(.text*);
		*(.text*);
	}

	.rodate : {
		*(.rodata*);
	}

	.data : {
		*(.data*);
	}

	.bss : {
		*(.bss*);
	}

	__end = .;
}

