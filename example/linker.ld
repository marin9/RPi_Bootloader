ENTRY(start)
SECTIONS{
	. = 0x10000;

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
}
