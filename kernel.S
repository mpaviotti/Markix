
kernel.elf:     file format elf32-i386


Disassembly of section .text:

00010000 <_start>:
   10000:	e8 03 00 00 00       	call   10008 <main>
   10005:	eb fe                	jmp    10005 <_start+0x5>
   10007:	90                   	nop    

00010008 <main>:
   10008:	8d 4c 24 04          	lea    0x4(%esp),%ecx
   1000c:	83 e4 f0             	and    $0xfffffff0,%esp
   1000f:	ff 71 fc             	pushl  -0x4(%ecx)
   10012:	51                   	push   %ecx
   10013:	eb fe                	jmp    10013 <main+0xb>

Disassembly of section .comment:

00000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%edi)
   3:	43                   	inc    %ebx
   4:	3a 20                	cmp    (%eax),%ah
   6:	28 55 62             	sub    %dl,0x62(%ebp)
   9:	75 6e                	jne    79 <_start-0xff87>
   b:	74 75                	je     82 <_start-0xff7e>
   d:	20 34 2e             	and    %dh,(%esi,%ebp,1)
  10:	33 2e                	xor    (%esi),%ebp
  12:	33 2d 35 75 62 75    	xor    0x75627535,%ebp
  18:	6e                   	outsb  %ds:(%esi),(%dx)
  19:	74 75                	je     90 <_start-0xff70>
  1b:	34 29                	xor    $0x29,%al
  1d:	20 34 2e             	and    %dh,(%esi,%ebp,1)
  20:	33 2e                	xor    (%esi),%ebp
  22:	33 00                	xor    (%eax),%eax
