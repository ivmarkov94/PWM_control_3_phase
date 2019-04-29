#include "GPIO.h"

void rcc_ini(void)
{
      RCC->APB2ENR |= (1); //Активация тактирования Альтернативных функций в enable register     
	  RCC->APB2ENR |= (1<<4); //Активация тактирования GPIOC в enable register
	  //RCC->APB2ENR |= (1<<2); //Активация тактирования GPIOA в enable register
}

void port_ini(void)
{
	  GPIO_InitTypeDef myGPIO;
	
	  //LED
	  myGPIO.GPIO_Pin = GPIO_Pin_13; // инициализция параметров ножки порта прводится в регистре CRH  configuration register high
      myGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
      myGPIO.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &myGPIO);
}