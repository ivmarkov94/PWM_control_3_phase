#include "Interrupts.h"

//varible 
int i1 = 0, i2 = 33, i3 = 66;
uint32_t count_tic = 0;

//varible UART
extern int RX_FLAG_END_LINE;
extern char RX_BUF[RX_BUF_SIZE]; 
extern int RXi;

//varible Timers
extern volatile uint16_t *D1,*D2,*D3;

//varible Varible
extern int16_t SinTabl[100];

void TIM3_IRQHandler(void)
{
  if((TIM3->SR & TIM_SR_UIF) == 1){
            TIM3->SR &= ~TIM_SR_UIF;//Сбрасываем флаг UIF // Обязательно сбрасываем флаг 	
		    DWT_CYCCNT = 0;// обнуляем значение
            *D1 = SinTabl[i1];
            *D2 = SinTabl[i2];
            *D3 = SinTabl[i3];
            i1=i1+1;
            i2=i2+1;
            i3=i3+1;
            if(i1==POINT_ON_Tsin) i1=0;   
            if(i2==POINT_ON_Tsin) i2=0; 
            if(i3==POINT_ON_Tsin) i3=0;        
            //GPIOC->ODR ^= GPIO_Pin_13;
		    count_tic = DWT_CYCCNT;
  }
}

void USART1_IRQHandler(void) //обработчик прерываний
{
	  char RXc;
	
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET) //убеждаемся, что прилетел байт
    {
			  //__disable_irq();
        RXc = USART_ReceiveData(USART1);
        RX_BUF[RXi] = RXc;
        RXi++;
 
        if (RXc != '\n') {
							if (RXi > RX_BUF_SIZE-1) {
										clear_RXBuffer();
							}
        }
				else{
						RX_FLAG_END_LINE = 1;
			  }
        //Echo
        USART_SendData(USART1, RXc);			    
    }
		
}
