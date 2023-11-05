/* Linker script for STM32F412xx */

MEMORY {
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

PROVIDE(gMspInitial = ORIGIN(SRAM) + LENGTH(SRAM));  /* Initial value for the MSP (main stack pointer) */
EXTERN(gStm32VectorTable);
EXTERN(resetIsr)

SECTIONS {
	.vector_table ORIGIN(FLASH) : {
		KEEP(*(.vector_table.*));
	} > FLASH

	.text : {
		*(.text .text.*);
		KEEP(*(.text.resetIsr))
		*(glue_7)
		*(glue_7t)
		*(__fixunssfdi)
		*(__fixunsdfsi)
	} > FLASH

	.rodata : {
		. = ALIGN(4);
		*(.rodata .rodata.*);
	} > FLASH

	.ARM.extab : {
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} >FLASH

	.ARM : {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	} >FLASH


	/* Uninitialized (zero-initialized) static data */
	.bss : {
		. = ALIGN(4);
		gBssStart = .;
		*(.bss .bss.*)
		. = ALIGN(4);
		gBssEnd = .;
	} > SRAM

	/* Non zero-initialized static data */
	.data : AT(ADDR(.rodata) + SIZEOF(.rodata)) /* Map the initial values onto flash. */ {
		. = ALIGN(4);
		/* Pointer for further initialization of `.data`, mapped to RAM */
		gRamDataStart = .;
		*(.data .data.*);
		. = ALIGN(4);
		/* Pointer for further initialization of `.data`, mapped to RAM */
		gRamDataEnd = .;
	} > SRAM

	/* Provide a symbol of the non zero-initialized data's load address for
	 * forther use (mapped to Flash) */
	gFlashDataStart = LOADADDR(.data);

	/* The remaning space is where heap and stack reside */
	.heap_and_stack : {
		. = ALIGN(4);

		/* Symbol `end` is required for libc. The ARM toolchain "rustup" installs does not seem to provide standard
		libc's `malloc` calls or alternatives, so we borrow pre-compiled static `libc` and `libnosys` libraries from
		arm-none-eabi-gcc-10 package and wrap the memory managing code around it */

		PROVIDE(end = .);
	} > SRAM

/*	/DISCARD/ : {
		libc.a( * )
		libm.a( * )
		libgcc.a( * )
	}*/
}
