.extern _irq_handler

.globl isr_default
.globl isr_common
.globl isr_0
.globl isr_1
.globl isr_2
.globl isr_3
.globl isr_4
.globl isr_5
.globl isr_6
.globl isr_7
.globl isr_8
.globl isr_9
.globl isr_10
.globl isr_11
.globl isr_12
.globl isr_13
.globl isr_14
.globl isr_15
.globl isr_16
.globl isr_17
.globl isr_18

.globl isr_32
.globl isr_33
.globl isr_34
.globl isr_35
.globl isr_36
.globl isr_37
.globl isr_38
.globl isr_39
.globl isr_40
.globl isr_41
.globl isr_42
.globl isr_43
.globl isr_44
.globl isr_45
.globl isr_46
.globl isr_47
.globl isr_48

/* Segue una lista degli entry point
che andranno nella IDT */
	
isr_0:          # division by zero exception
    cli
    push $0     
    jmp isr_common

isr_1:          # debug exception
    cli
    push $1     
    jmp isr_common

isr_2:          # non maskable interrupt
    cli
    push $2     
    jmp isr_common

isr_3:          # breakpoint
    cli
    push $3     
    jmp isr_common

isr_4:          # into detected overflow
    cli
    push $4     
    jmp isr_common

isr_5:          # out of bounds
    cli
    push $5     
    jmp isr_common

isr_6:          # invalid opcode
    cli
    push $6     
    jmp isr_common

isr_7:          # no coprocessor
    cli
    push $7     
    jmp isr_common

isr_8:          # double fault exception
    cli
    
    push $8     
    jmp isr_common

isr_9:          # coprocessor segment overrun
    cli
         # Codice di errore fittizio.
    push $9     
    jmp isr_common

isr_10:          # bad TSS
    cli
    push $10     
    jmp isr_common

isr_11:          # segment not present
    cli
    push $11     
    jmp isr_common

isr_12:          # stack fault
    cli
    push $12     
    jmp isr_common

isr_13:          # general protection fault
    cli
    push $13     
    jmp isr_common

isr_14:          # page fault
    cli
    push $14     
    jmp isr_common

isr_15:          # unknown interrupt
    cli
         
    push $15     
    jmp isr_common

isr_16:          # coprocessor fault
    cli
         
    push $16     
    jmp isr_common

isr_17:          # alignment check exception
    cli  
    push $17     
    jmp isr_common

isr_18:          # machine check exception
    cli         
    push $18     
    jmp isr_common


isr_32:         # IRQ 0: timer
    cli
    push $32    
    jmp isr_common

isr_33:         # IRQ 1: tastiera
    cli
    push $33     
    jmp isr_common

isr_34:         # IRQ 1: tastiera
    cli
    push $34     
    jmp isr_common

isr_35:         # IRQ 1: tastiera
    cli
    push $35     
    jmp isr_common

isr_36:         # IRQ 1: tastiera
    cli
    push $36     
    jmp isr_common

isr_37:         # IRQ 1: tastiera
    cli
    push $37     
    jmp isr_common

isr_38:         # IRQ 1: tastiera
    cli
    push $38     
    jmp isr_common

isr_39:         # IRQ 1: tastiera
    cli
    push $39     
    jmp isr_common

isr_40:         # IRQ 1: tastiera
    cli
    push $40     
    jmp isr_common

isr_41:         # IRQ 1: tastiera
    cli
    push $41     
    jmp isr_common

isr_42:         # IRQ 14: canale IDE primario 
    cli
    
    push $42    
    jmp isr_common

isr_43:         # IRQ 15: canale IDE secondario
    cli
    
    push $43    
    jmp isr_common

isr_44:         # IRQ 1: tastiera
    cli
    push $44     
    jmp isr_common

isr_45:         # IRQ 1: tastiera
    cli
    push $45     
    jmp isr_common

isr_46:         # IRQ 1: tastiera
    cli
    push $46     
    jmp isr_common

isr_47:         # IRQ 1: tastiera
    cli
    push $47     
    jmp isr_common

isr_48:         # IRQ 1: tastiera
    cli
    push $48
    jmp isr_common

/* Nel caso di una entry nella IDT
	non prevista si imposta questo handler */
isr_default:
	cli
	push $-1
	jmp isr_common


/* Tutte gli entry point inseriscono nello stack
il numero della entry e fanno un jump a isr_common
che salva il contesto e chiama
interrupt/idt.c: _irq_handler(unsigned int stack)
passandogli l'indirizzo dello stack

al termine di _irq_handler lo stack potrebbe
essere cambiato, è qui che avviene il cambio di contesto.
*/
isr_common:
	cli
	pusha

	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	
	movl  %esp, %eax
	pushl %eax
	call _irq_handler
	popl %eax
	mov %eax, %esp

	popl %gs
	popl %fs
	popl %es
	popl %ds

	popa
	add $4, %esp
	sti
	iret
	