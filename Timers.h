#ifndef TIMERS_H_
#define TIMERS_H_


#include "stm32f10x.h"

#include "Variable.h"
//prototypes

void timer_ini(void);//инициализация таймеров 

//macross

//constants
#define TIM1_CH1N_PB        13
#define TIM1_CH1_PA         8
#define TIM1_CH2_PA         9

#define LED1_G_PC           9
#define LED2_B_PC           8

#define PWM_VALUE           20
#define TMR_T               50
#define DEADTIME            5

#endif /*TIMERS_H_*/

