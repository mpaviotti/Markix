#ifndef __PIT8253_H
#define __PIT8253_H

/* Impostare TIMER_MSEC per selezionare
   l'intervallo dell'interrupt in millisecondi */
#define TIMER_MSEC 20
#define TIMER_HZ (1/MSEC*1000)
#define TIMER_FREQ 1193182L
#define TIMER_COUNTER ((unsigned)(FREQ_TIMER / TIMER_HZ))

/*
  Comando da inviare prima di impostare 
  il TIMER_COUNTER:

  0 0 = Channel 0
  1 1 = Access mode: lobyte/hibyte
  0 1 1 = Mode 3 (square wave generator)
  0 Binary mode
*/
#define TIMER_CTRL_COMMAND 0x36

/* Porte del TIMER */
#define TIMER_CHAN_0 0x40
#define TIMER_CHAN_1 0x41
#define TIMER_CHAN_2 0x42
#define TIMER_CTRL   0x43


extern void init_pit8253(void);
#endif
