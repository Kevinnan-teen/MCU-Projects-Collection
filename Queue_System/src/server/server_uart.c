#include "server_uart.h"
#include <reg52.h>

void initSCON(){
	SCON = 0X40;	//串口同坐在方式0，允许发送
	TMOD = 0X21;	//T1工作在方式2，8位自动重装
	PCON = 0X00;	//波特率不倍增
	TH1 = 0XFD;		//波特率设置为9600
	TL1 = 0XFD;
	TI = 0;
	TR1 = 1;
}


void send(unsigned char state){
	SBUF = state;
	while(TI == 0);
	TI = 0;
}