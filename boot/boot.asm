	;; Markix's BootLoader
	
	;; per capire questo codice è consigliabile
	;; leggere "intel 80386 programmer's reference manual"

[BITS 16]       ;è codice a 16 bit perchè siamo in real-mode
	;;  i primi 512 bytes vengono caricati all' indirizzo 0x7c00 

	[ORG 0x7C00]	

	xor 	ax, ax
	mov	ds, ax
	mov	ss, ax
	mov	sp, 0xFFFE	

	
	mov	bx,LOADING
	call	write

	;; procedura classica per il
	;; passaggio in Protected Mode
	;; 1) caricamento del kernel dal floppy a 0x10000
	call	carica_kernel
	
	mov	bx, OK
	call	write
	;; 2) disabilitazione interrupts
	cli
	
	in	al,0x70
	or	al,0x80
	out	0x70,al

	;; 3) abilitazione linea A20
wait1:
  	in  al, 0x64
  	test  al, 2
  	jnz wait1
  	mov al, 0xD1
 	out 0x64, al

wait2:
	in  al, 0x64
	and ax, byte 2
	jnz wait2
	mov al, 0xDF
  	out 0x60, al
	
	;; 4) caricamento della GDT
	lgdt	[gdtinfo]

	;; 5) impostazione del bit PE del registro CR0
	mov	eax,	CR0
	or	al,	1
	mov	CR0,	eax

	mov	ax, 	0x10
	mov	ds,	ax

	; Floppy motor-off
	mov	dx, 0x3F2
	mov	al, 0xC
	out	dx, al

	;; 6) far jump al codice a 32 bit
	jmp	dword 0x08:run

	
[BITS 16]
write:
        pusha   		
	push es 		
	xor ax, ax      	
	mov es, ax		
	xor di, di      	
conteggio:      		
	cmp  byte[es:bx+di], 0  
	je fine         	
	mov ah, 0Eh     	
	mov al, byte[es:bx+di]  
	
	push bx 		
	mov bh, 0
	int 10h
	pop bx
	
	inc di
	jmp conteggio
fine:   	
	pop es
        popa
	ret
	
carica_kernel:
	mov	di, 80

	;;ES:BX contiene l'indirizzo dove
	;;int 13h metterà i settori letti
	;;(un settore = 512byte)
	mov 	ax, 0x10000	
	mov 	es, ax
	
	mov 	ch, 0
	mov 	cl, 2	

	mov 	dh, 0		
	mov	dl, 0
	
	xor 	bx, bx

leggi:
	mov 	ah, 02h		;servizio 02h: leggi settore 
	mov	al, 01h		;un settore alla volta

	int 	0x13		;legge 512b (aka 64byte) e mette in es:bx
	
	mov	ax,	es
	add	ax,	0x20	;incrementa ES di 32bit=0x20 (0x20*16h=0x40=64d)
	mov	es,	ax

	push 	bx
	mov	bx, DOT
	call 	write
	pop	bx
	
	dec	di		
	jz	caricato	

	inc 	cl		
	cmp	cl, 18		
	jbe	leggi		

	mov	cl, 0x01	
	

	inc	dh		
	cmp 	dh, 2
	jne	leggi

	mov	dh, 0		
	inc	ch		
	jmp 	leggi
	
caricato:
	ret
	;;qui inizia la dichiarazione della GDT
	;; lgdt carica la lunghezza e l'indirizzo
	
gdtinfo:        
	dw  gdtlength   
	dd  gdt_table   
	
gdt_table:
	;; 3 descrittori : null_desc, flat_code, flat_data
	;; fare riferimento al manuale
	;; intel per il significato
	;; dei bit
null_desc:
    dd  0	
    dd  0

flat_code:
    dw  0xFFFF  ; segment limit  0->15
    dw  0x0000  ; base segement 0->15
    db  0x00 	; base segment 16->23
    db  0x9A	; P=1 DPL=00b DT=1 CODE=1 C=0 R=1 A=0
    db  0xCF  	; G=1 D/G=1 0 AVL=0 and segment lmit 16->19=0xF
    db  0x00  	; base segment 24->32

flat_data:
    dw  0xFFFF  ; segment limit  0->15
    dw  0x0000  ; base segement 0->15
    db  0x00  	; base segment 16->23
    db  0x92  	; P=1 DPL=00b DT=1 DATA=0 E=0 W=1 A=0
    db  0xCF  	; G=1 D/G=1 0 AVL=0 and segment lmit 16->19=0xF
    db  0x00  	; base segment 24->32

gdtlength equ $ - gdt_table  ;calcola la dimensione della tabella

[BITS 32]
run:
	mov	ax,	0x10
	mov	ds,	ax
	mov	es, 	ax
	mov	ss, 	ax
	mov	esp,	0x400000
	push	dword	0x2
	popfd

	mov	eax,	0x100000
	
	cli 

	jmp	dword 	0x100000
	
	;; dichiarazione delle variabili da stampare
LOADING		db	'Loading kernel',0
DOT		db	'.',0
OK		db	'OK.',13,10,0
FDC_ERROR	db	' Errore nella lettura del floppy.', 0xD, 0xA, 0xD, 0xA,  0x0

	;; questo codice deve
	;; essere grande 512bit per stare nel boot
	;; sector e terminare con
	;; 0xAA55
times 510-($-$$) db 0
dw 0xAA55      







