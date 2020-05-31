ENTRY(_start)
SECTIONS{
	. = 0x8000;

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
}
