    ;; Markix's BootLoader
	
	;; per capire questo codice è consigliabile
	;; leggere "intel 80386 programmer's reference manual"

[BITS 16]       ;è codice a 16 bit perchè siamo in real-mode
[ORG 0x7C00]    ;i primi 512 bytes vengono caricati all' indirizzo 0x7c00

	xor 	ax, ax
	mov	ds, ax
	mov	ss, ax
	mov	sp, 0xFFFE	

	mov	bx,LOADING
	call	write

loop:
	hlt
	jmp loop
	
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

	
	;; dichiarazione delle variabili da stampare
LOADING		db	'Loading kernel',0
DOT		db	'.',0
OK		db	'OK.',13,10,0
	
	;; questo codice deve
	;; essere grande 512bit per stare nel boot
	;; sector e terminare con
	;; 0xAA55
	
times 510-($-$$) db 0
dw 0xAA55      







