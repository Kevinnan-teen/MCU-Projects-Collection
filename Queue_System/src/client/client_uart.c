#include "client_uart.h"
#include <reg52.h>


void initSCON(){
	SCON = 0X50;	//串口工作在方式1，允许接收
	TMOD = 0X20;	//T1工作在方式2，8位自动装载
	PCON = 0X00;	//波特率不倍增
	TH1 = 0XFD;		//波特率设置为9600
	TL1 = 0XFD;
	RI = 0;
	TR1 = 1;
}

unsigned char receive(){
	unsigned char state;
	while(RI == 0);
	state = SBUF;
	RI = 0;
	return state;
}

