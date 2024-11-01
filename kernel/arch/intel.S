#include "intel.h"
	
	
.sect .text
.sect .rom
.sect .data
.sect .bss

.global load_idt
.global stack_dump
	
.sect .text

/* Carica  la dimensione e l'indirizzo
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
