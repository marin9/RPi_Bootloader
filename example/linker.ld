ENTRY(start)
SECTIONS{
	. = 0x8000;

	.init : {
		*(.init*);
	}

	.text : {
		*(.text*);
	}

	.data : {
		*(.data*);
	}

	.bss : {
		*(.bss*);
	}

	. = . + 0x1000;
	stack = .;
}
