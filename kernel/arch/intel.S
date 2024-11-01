#include "intel.h"
	
.sect .text
.sect .rom
.sect .data
.sect .bss
	
.global save
.global restore
.global load_idt
.global stack_dump
	
.sect .text

/* Salva il valore dei flags */
save:
	pushl	%ebp
	movl	%esp,	%ebp
	addl	$8,	%ebp
	pushfl
	popl 	(%ebp)
	popl 	%ebp
	ret

/* Ripristina i valori dei Flags */
restore:
	pushl	%ebp
	movl	%esp,	%ebp
	addl	$8,	%ebp
	pushl	(%ebp)
	popfl
	popl	%ebp
	ret

/* Carica la la dimensione e l'indirizzo
della IDT nel registro IDTR */
load_idt:
	pushl	%ebp
	movl	%esp,	%ebp
	movl	8(%ebp),%eax
	lidt 	(%eax)
	popl	%ebp
	ret

/* Ritorna il valore dello SP */
stack_dump:
	mov 	%esp,	%eax
	ret
	
