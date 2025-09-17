ENTRY(start)

SECTIONS {
    . = 1M;
    .text :
    {
        *(.multiboot_header)
        *(.text)
        *(.text.*)
    }
    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
    }
    .data :
    {
        *(.data)
        *(.data.*)
    }
    .rela.dyn :
    {
        *(.rela.dyn)
    }
    .bss :
    {
        *(.bss)
        *(.bss.*)
    }
}
