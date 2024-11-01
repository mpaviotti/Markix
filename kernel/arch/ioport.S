.sect .text
.sect .rom
.sect .data
.sect .bss

.global inw
.global outw

.global inb
.global outb

.global io_wait
	
.sect .text

inw:
	pushl 	%ebp
	movl	%esp,		%ebp
	movl	8(%ebp),	%edx	//primo argomento
	inw 	%dx, 		%ax	//porta, valore
	popl	%ebp
	ret

outw:
	pushl	%ebp
	movl	%esp,		%ebp
	movl	8(%ebp),	%eax	//primo argomento	
	movl	12(%ebp), 	%edx	//secondo argomento
	outw 	%ax, 		%dx	//valore, porta
	popl	%ebp
	ret

inb:
	pushl 	%ebp
	movl	%esp,		%ebp
	movl	8(%ebp),	%edx	//primo argomento
	inb 	%dx, 		%al	//porta, valore
	popl	%ebp
	ret

outb:
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
