ENTRY(start)
SECTIONS {
	. = 0x8000;

	.text : {
		start.o(.text*);
		*(.text*);
	}

	.rodata : {
		*(.rodata*);
	}

	.data : {
		*(.data*);
	}

	.bss : {
		*(.bss*);
	}
}
