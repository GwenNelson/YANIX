ENTRY(_start)

SECTIONS
{

    . = 0xC0100000;

    _kernel_start = .;

    .text ALIGN(4K) : AT (ADDR (.text) - 0xC0000000)
    {
	*(.multiboot)
    	    code = .; _code = .; __code = .;
	*(.text)
        . = ALIGN(4096);
	ecode = .; _ecode = .; __ecode = .;
    }

    .data  ALIGN(4K) : AT (ADDR (.data) - 0xC0000000)
    {
        data = .; _data = .; __data = .;
        *(.data)
	. = ALIGN(4096);
	*(.rodata)

	_edata = .;
    }

    .stab  ALIGN(4K) : AT (ADDR (.stab) - 0xC0000000) {
		PROVIDE(__STAB_BEGIN__ = .);
		*(.stab);
		PROVIDE(__STAB_END__ = .);
		BYTE(0)		/* Force the linker to allocate space
				   for this section */
	}

	.stabstr  ALIGN(4K) : AT (ADDR (.stabstr) - 0xC0000000){
		PROVIDE(__STABSTR_BEGIN__ = .);
		*(.stabstr);
		PROVIDE(__STABSTR_END__ = .);
		BYTE(0)		/* Force the linker to allocate space
				   for this section */
	}


    .bss  ALIGN(4K) : AT (ADDR (.bss) - 0xC0000000)
    {
        bss = .; _bss = .; __bss = .;
	*(.COMMON)
	*(.bss)
	*(.bootstrap_stack)
        . = ALIGN(4096);
	_ebss = .;
	edata = .;
    }

    _kernel_end = .;
    end = .; _end = .; __end = .;
}
