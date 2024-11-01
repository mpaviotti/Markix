
.sect .text
.sect .rom
.sect .data
.sect .bss
	
.global switch_mode
.global load_tr
.global load_gdt
.global setup_seg
	
.sect .text

switch_mode:
	pushl %ebp
	cli	
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	pushl $0x23
	pushl %eax
	pushf
	mov $0x200, %eax
	push %eax
	pushl $0x1B
	push $1f
	iret;
1:	
	popl %ebp
	ret
load_tr:
	pushl %ebp
	movl %esp, %ebp
	
	pushl %eax
	xorl %eax, %eax
	movb 8(%ebp), %al
	ltr %ax
	popl %eax

	popl %ebp
	ret
	
load_gdt:
	pushl	%ebp
	movl	%esp,	%ebp
	movl	8(%ebp),%eax
	lgdt 	(%eax)
	popl	%ebp
	ret


setup_seg:
	push %eax
	movw $0x10,%ax
	movw %ax,%ds
	movw %ax,%es
	movw %ax,%fs
	movw %ax,%gs
	movw %ax,%ss
	ljmp $0x08,$next
	nop
	nop
next:	
	pop %eax
	ret
