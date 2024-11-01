.sect .text
.sect .rom
.sect .data
.sect .bss
	
.global outportb
.global inportb
.global io_wait
	
.sect .text
	
inportb:
	pushl 	%ebp
	movl	%esp,		%ebp
	movl	8(%ebp),	%edx	//primo argomento
	inb 	%dx, 		%al	//porta, valore
	popl	%ebp
	ret

outportb:
	pushl	%ebp
	movl	%esp,		%ebp
	movl	8(%ebp),	%eax	//primo argomento	
	movl	12(%ebp), 	%edx	//secondo argomento
	outb 	%al, 		%dx	//valore, porta
	popl	%ebp
	ret

io_wait:
	jmp 	1f
1:
	jmp 	1f
1:
	ret
.sect .data
