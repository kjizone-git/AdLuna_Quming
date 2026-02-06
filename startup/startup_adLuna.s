
	.section .text
    .global _Reset_Start
	.type _Reset_Start, @function
	.align 2
_Reset_Start:

/* initialize stack pointer */    
    
    ldi _stack - 8,%r8 /*  stack pointer , use internal memory */
    mov %r8,%sp
	
	jal __startup
	
.size _Reset_Start, .-_Reset_Start
.section ._stack
_stack:    .long     1

