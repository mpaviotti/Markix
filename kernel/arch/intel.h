#ifndef __INTEL_H
#define __INTEL_H

/* Istruzioni ASM che meritano di essere 
confinate in arch/ */
#define iret() asm("iret")
#define cli() asm("cli")
#define sti() asm("sti")

#endif
