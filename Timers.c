#include "Timers.h"
//varible
volatile uint16_t *D1,*D2,*D3;

//varible Variable
extern int32_t Fshim, Fsin; //Частота ШИМ;


void timer_ini(void)
{ 
    
	  NVIC_InitTypeDef myNVIC;
	  GPIO_InitTypeDef myGPIO;
//	  TIM_TimeBaseInitTypeDef TIMER_InitStructure;
//	
//      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//      TIM_TimeBaseStructInit(&TIMER_InitStructure);
//      TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//      TIMER_InitStructure.TIM_Prescaler = 72-1;//             1000000hz или 1MHz
//      TIMER_InitStructure.TIM_Period = 200;//// Fsin*POINT_ON_Tsin это и есть частота ншего таймера
//      TIM_TimeBaseInit(TIM3, &TIMER_InitStructure);
//      TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//      TIM_Cmd(TIM3, ENABLE);
    //-TIM3_Формируется синус-----------------------------------------------------------------------------------------------
    RCC->APB1ENR|=(1<<1); //Активация тактирования TIM3 в enable register
    TIM3->PSC = 72 - 1; //72MHz     // (частота тактирования У нас 72000000)/(PSC+1) = Частота счёта таймера 
    TIM3->ARR = (1000000/POINT_ON_Tsin)/Fsin;// Fsin*POINT_ON_Tsin это и есть частота нашего таймера; Частота вывода точки синуса должна быть больше, частоты синуса в N раз; Где N - количество точек из скольки состоит синус
    TIM3->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
    //TIM3->EGR|=TIM_EGR_UG;//событие обносления для обновления регистров
    /* NVIC Configuration */
    /* Enable the TIM3_IRQn Interrupt */
    myNVIC.NVIC_IRQChannel = TIM3_IRQn;
    myNVIC.NVIC_IRQChannelPreemptionPriority = 0;
    myNVIC.NVIC_IRQChannelSubPriority = 0;
    myNVIC.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&myNVIC);	
//	//-------------------------------------------------------------------------------------------------------------------TIM3  
	
//	//TIM2_PWM_for_1_channel-------------------------------------------------------------------------------------------------
//    RCC->APB1ENR|=1; //Активация тактирования TIM2 в enable register
//    TIM2->PSC = 12 - 1;//6MHz // (частота тактирования У нас 72000000)/(PSC+1) = Частота счёта таймера 
//    TIM2->ARR =6000000/Fshim;  ////5кHz; 1200 точек на период пилы;    //Period предел счета таймера досчитав до ARR будет вызываться прерывание в нашем случае 

//    RCC->APB2ENR|=(1<<2);//Активация тактирования GPIOA в enable register 
//    myGPIO.GPIO_Pin   = GPIO_Pin_0; //первый канал таймера
//    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
//    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_Init(GPIOA,&myGPIO);
//		
//    TIM2->CCER  |=1; //Разрешаем таймеру использовать первый канал( ножка PA.) в регистре TIMx_CCER capture/compare enable register
//    TIM2->CCER  |=(1<<1); //активный уровень ноль TIMx_CCER capture/compare enable register
//    TIM2->CCMR1 |=(1<<5)|(1<<6); //Включаем на первом канале обртный ШИМ    УПРАВЛЕНИЕ ДРЙВЕРАМИ НУЛЕМ
//    D1 = &(TIM2->CCR1); //скважность в периоде
//    //TIM2->EGR|=TIM_EGR_UG;//событие обносления для обновления регистров
//	//-------------------------------------------------------------------------------------------------------------------TIM2
//    *D1=6000000/Fshim/2;
    RCC->APB2ENR|=(1<<2);//Активация тактирования GPIOA в enable register 
    myGPIO.GPIO_Pin   = GPIO_Pin_8; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&myGPIO);
    RCC->APB2ENR|=(1<<3);//Активация тактирования GPIOB в enable register 
    myGPIO.GPIO_Pin   = GPIO_Pin_13; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&myGPIO);
    
    myGPIO.GPIO_Pin   = GPIO_Pin_9; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&myGPIO);
    myGPIO.GPIO_Pin   = GPIO_Pin_14; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&myGPIO);
    
    myGPIO.GPIO_Pin   = GPIO_Pin_10; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&myGPIO);
    RCC->APB2ENR|=(1<<3);//Активация тактирования GPIOB в enable register 
    myGPIO.GPIO_Pin   = GPIO_Pin_15; //первый комплементарный канал таймера
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&myGPIO);
    
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN;
    TIM1->PSC = 12 - 1;//6MHz // (частота тактирования У нас 72000000)/(PSC+1) = Частота счёта таймера 
    TIM1->ARR =6000000/Fshim;//5кHz; 1200 точек на период пилы;    //Period предел счета таймера досчитав до ARR будет вызываться прерывание в нашем случае 
    
    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE |    TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE; //Включаем на первом канале ШИМ  PWM mode 1
    TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE ;
    TIM1->CCER=(TIM_CCER_CC1E | TIM_CCER_CC1NE) | (TIM_CCER_CC2E | TIM_CCER_CC2NE) | (TIM_CCER_CC3E | TIM_CCER_CC3NE); //активируем каналы
    //TIM1->CCER|=TIM_CCER_CC1NP|TIM_CCER_CC1P;//1 упр высоким уровнем; 0 управление низким уровнем
    TIM1->BDTR=TIM_BDTR_MOE|DEADTIME;// активируем каналы 2 раз
    //TIM1->CR1=TIM_CR1_ARPE; //ARR регистр обновляется по флагу UIF  стр299
    TIM1->CR1 = TIM_CR1_CMS_1 | TIM_CR1_CMS_0;
    TIM1->CR1|=TIM_CR1_CEN; // Начать отсчёт таймера!
    TIM1->EGR=TIM_EGR_UG; //обновим регистры 
    
    D1 = &(TIM1->CCR1);   //скважность в периоде
    D2 = &(TIM1->CCR2);   //скважность в периоде
    D3 = &(TIM1->CCR3);   //скважность в периоде
    *D1=6000000/Fshim/2;
    
    
    TIM3->CR1 |= TIM_CR1_CEN;   
}
