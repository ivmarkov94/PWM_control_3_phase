#include "Variable.h"

//varible UART
extern int RX_FLAG_END_LINE;

//varible 
int32_t Fshim, Fsin; //Частота ШИМ; Количество каналов;
int16_t SinTabl[POINT_ON_Tsin];
//varible SysControl
//extern int8_t Mode;
	
void variable_ini(void)
{
	int32_t i;
	//Инициализция переменных при включении
	RX_FLAG_END_LINE=0;
	Fshim=40000;
    Fsin=50;
	///Mode=STOP;
	for(i=0;i<=(POINT_ON_Tsin-1); i++){
        SinTabl[i]=roundf( (6000000/Fshim/2)*(1+sin(0.0628*i)) );
	}
	
}
