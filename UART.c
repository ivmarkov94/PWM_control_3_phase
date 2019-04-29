#include "UART.h"

//varible
int  RX_FLAG_END_LINE;
char RX_BUF[RX_BUF_SIZE] = {'\0'}; 
char bufferDMA[bufferDMA_SIZE] = {'\0'}; 
char NumRX[NUM_RX_BUF_SIZE];
int  RXi;



void usart_ini(void)
{
	NVIC_InitTypeDef myNVIC;
    GPIO_InitTypeDef myGPIO; 
    USART_InitTypeDef myUSART;

    RCC->APB1ENR |= (1<<18); //Активация тактирования UART3 в enable register
	RCC->APB2ENR |= (1<<3);  //Активация тактирования GPIOB в enable register 

	
    myGPIO.GPIO_Pin   = GPIO_Pin_10; //TX
    myGPIO.GPIO_Mode  = GPIO_Mode_AF_PP;
    myGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&myGPIO);
    myGPIO.GPIO_Pin   = GPIO_Pin_11; //RX
    myGPIO.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    myGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&myGPIO);
    
    //инициализация USART 
    myUSART.USART_BaudRate = 57600;                                       //проходит в Control register 1 (USART_CR1/2/3)
    myUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
    myUSART.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
    myUSART.USART_Parity = USART_Parity_No; //бит четности
    myUSART.USART_StopBits = USART_StopBits_1; //количество стоп битов
    myUSART.USART_WordLength = USART_WordLength_8b; //количество бит в посылке
    USART_Init(USART3,&myUSART);
    
//		//инициализация DMA 
//    RCC->AHBENR |= (1<<0); //Активация тактирования DMA в enable register
//    DMA_InitTypeDef DMA_InitStruct;
//    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR); //адрес периферийного устройства 
//    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&bufferDMA[0]; //адрес памяти 
//    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //устройство  source or destination
//    DMA_InitStruct.DMA_BufferSize = buffer_SIZE; //размер буфера данных
//    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //указывает надо ли инкрементировать адреса данных в периферии (DMA_PeripheralInc_Enable | DMA_PeripheralInc_Disable)
//    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//указывает надо ли инкрементировать адреса данных в памяти (DMA_MemoryInc_Enable | DMA_MemoryInc_Disable)
//    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//размер единицы данных для переферии
//    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// размер единицы данных для памяти
//    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//режим работи канала DMA (DMA_Mode_Circular | DMA_Mode_Normal)
//    DMA_InitStruct.DMA_Priority = DMA_Priority_Low;//приоритет канала DMA (DMA_Priority_VeryHigh | DMA_Priority_High | DMA_Priority_Medium | DMA_Priority_Low)
//    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//передача память > память (DMA_M2M_Enable | DMA_M2M_Disable)
//    DMA_Init(DMA1_Channel4, &DMA_InitStruct);

      /* Enable DMA REC*/
//    USART1->CR3|=(1<<7);//DMA enable transmitter //запрос работы с DMA
		
		/* Enable Interrupt DMA Transfer complete */
//		DMA1_Channel4->CCR|=(1<<1); //Transfer complete interrupt enable
		
		//DMA1_Channel4_IRQn 
//		NVIC_EnableIRQ(DMA1_Channel4_IRQn);
 
    /* Enable the USARTx Interrupt */
    myNVIC.NVIC_IRQChannel = USART3_IRQn; 
    myNVIC.NVIC_IRQChannelPreemptionPriority = 1; //Приоритет
    myNVIC.NVIC_IRQChannelSubPriority = 0; //Субприоритет
    myNVIC.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&myNVIC);
	  
	/* Enable USART3 */
    USART3->CR1|=(1<<13);// USART_Cmd(USART1, ENABLE);//   Control register 
    /* Enable the USART1 Receive interrupt: this interrupt is generated when the
    USART1 receive data register is not empty */
	USART3->CR1|=(1<<5);// USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  // проходит в Control register 1
		
	RX_FLAG_END_LINE=0;
	clear_RXBuffer();
}

 void USARTSend( const char *pucBuffer )
{
	int i=0;
	
    while (*(pucBuffer+i)!='\0')
		{
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) //проверяет Transmission Complete flag
        {
        }	
			  USART_SendData(USART3, *(pucBuffer+i));
		    i++;	
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) //проверяет Transmission Complete flag
        {
        }				
    }
}

//void USARTSendDMA(const char *pucBuffer)
//{
//	 while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) //проверяет Transmission Complete flag ЧТОБЫ НЕ ПЕРЕБИТЬ ЭХО ПРИЕМА
//        {
//        }		
//	strcpy(bufferDMA, pucBuffer);//данные копируются в память bufferDMA
//    /* Restart DMA Channel*/
//	DMA_Cmd(DMA1_Channel4, DISABLE); //отк дма
//	DMA1_Channel4->CNDTR = strlen(pucBuffer); //ввод количества посылок в UART из памяти  CNDTR после передачи уменьшиется на 1 декрементируется
//	DMA_Cmd(DMA1_Channel4, ENABLE);//вкл дма
//}
 
//void DMA1_Channel4_IRQHandler(void) //прерывание Transfer complete 
//{
//	DMA_ClearITPendingBit(DMA1_IT_TC4); // сбрасывает флаг выполнения передачи после отправки всех посылок 
//  DMA_Cmd(DMA1_Channel4, DISABLE);
//}

void clear_RXBuffer(void) {
	  int i=0;
	
      for (i=0; i<RX_BUF_SIZE; i++) RX_BUF[i] = '\0';
	  for (i=0; i<NUM_RX_BUF_SIZE; i++) NumRX[i] = '\0';
	  
	  RXi = 0;
}


