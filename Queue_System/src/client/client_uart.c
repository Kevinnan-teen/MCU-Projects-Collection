#include "client_uart.h"
#include <reg52.h>


void initSCON(){
	SCON = 0X50;	//���ڹ����ڷ�ʽ1���������
	TMOD = 0X20;	//T1�����ڷ�ʽ2��8λ�Զ�װ��
	PCON = 0X00;	//�����ʲ�����
	TH1 = 0XFD;		//����������Ϊ9600
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

