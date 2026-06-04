ENTRY(_start)

SECTIONS {
    . = 1M;
    .text : {
        *header.s.o(.multiboot)
        *(.multiboot)
        *(.text)
    }
    .data : { *(.data) }
    
    .bss  : { *(.bss)  }

    . = ALIGN(4096);
    end = .;
}