#include "main.h"

	
//varible UART
extern int RX_FLAG_END_LINE;
extern char RX_BUF[RX_BUF_SIZE];

//varible
char buffer[buffer_SIZE]; 
	 
int main(void)
{
	  /* Set NVIC Priority Group */
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//выбор группы приоритетов 
	  
      SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;// разрешаем использовать DWT
	  DWT_CYCCNT = 0;// обнуляем значение
	  
      // иницилизация
	  variable_ini();	
	  
	  rcc_ini();
	  port_ini();
	  SysClock_ini(); 
      usart_ini();  
	  timer_ini();
	
      USARTSend((" Hello!\r\n"));
      USARTSend((" I am Invertor!\r\n"));
    while(1){ 
         USARTSend((" TEST GIT!\r\n"));
//---ОБРАБОТКА ПРИНЯТЫХ С ПК ДАННЫХ----------------------------------------------------------
        if (RX_FLAG_END_LINE == 1) {
        USARTSend((" ZasholMASTER!\r\n"));            
//		    if(strncmp(RX_BUF, "Fshim=\r\n", 6)==0){ 
//			    USARTSend("COMMAND: Fshim=!\r\n");
//				i=6;
//				while(RX_BUF[i]!='\0'){
//				    NumRX[i-6]=RX_BUF[i];
//					i++;
//			        }
//			    Fshim = atoi(NumRX);		
//			    sprintf(buffer, "Fshim=%d\r\n", Fshim);
//			    USARTSend(buffer);
//			    Spi2_Read_Send_Data(MAINsendFshim, ALLSLAVE);
//			    Spi2_Read_Send_Data(round(Fshim/8), ALLSLAVE);//МАКСИМАЛЬНОЕ ЧИСЛО 32767*4=131068 которое можно отправить через данную функцию 
//		    }							 
//            if(strncmp(RX_BUF, "CLB\r\n", 5)==0){
//                USARTSend("COMMAND: Sensors Calibratcscion!\r\n");
//                //Calibration=ON;
//            }
//		    if(strncmp(RX_BUF, "STOP\r\n", 6)==0){
//		        USARTSend("COMMAND: STOP!\r\n");
//			    Spi2_Read_Send_Data(MAINsendSTOP, ALLSLAVE);// Отправляем запрос стопа
//			    Mode=STOP;				 
//		    }		 
		    if(strncmp(RX_BUF, "START\r\n", 7)==0){
		        USARTSend("COMMAND: START!\r\n");
			    //Mode=START;							 
		    }
            RX_FLAG_END_LINE = 0;		
            clear_RXBuffer();
        }
//------------------------------------------------------------------------------ОБРАБОТКА ПРИНЯТЫХ С ПК ДАННЫХ		
    }//конец основного while
    
}

