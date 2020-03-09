/* useful reference: www.linuxselfhelp.com/gnu/ld/html_chapter/ld_toc.html */
/* Written by Frank Duignan */
MEMORY
{
    flash : org = 0x10001000, len = 64k
    ram : org = 0x20000000, len = 16k
}
  
SECTIONS
{
        
	. = ORIGIN(flash);
        .text : {		  
		  *(.vectors); /* The interrupt vectors */
		  *(.text);
        } >flash
	. = ORIGIN(ram);
        .data : {	  
	  INIT_DATA_VALUES = LOADADDR(.data);
	  INIT_DATA_START = .;
		*(.remapped_vectors);
	    *(.data);
	  INIT_DATA_END = .;
        } >ram AT>flash
	BSS_START = .;
	.bss : {
	  
	    *(.bss);
	  
	} > ram
	BSS_END = .;
}
