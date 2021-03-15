#include "server_uart.h"
#include <reg52.h>

void initSCON(){
	SCON = 0X40;	//����ͬ���ڷ�ʽ0��������
	TMOD = 0X21;	//T1�����ڷ�ʽ2��8λ�Զ���װ
	PCON = 0X00;	//�����ʲ�����
	TH1 = 0XFD;		//����������Ϊ9600
	TL1 = 0XFD;
	TI = 0;
	TR1 = 1;
}


void send(unsigned char state){
	SBUF = state;
	while(TI == 0);
	TI = 0;
}