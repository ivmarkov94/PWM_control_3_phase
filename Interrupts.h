#ifndef Interrupts_H_
#define Interrupts_H_


#include "stm32f10x.h"
#include <math.h>

#include "UART.h"
#include "Variable.h"
//prototypes


//macross
#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
//constants
#define bufferTIM3_IRQ_SIZE 100 //буфер отправляемых данных

#endif /*Interrupts_H_*/

