#include <reg52.h>

#include "client_uart.h"
#include "lcd.h"

unsigned char code good[] = {0x47, 0x4f, 0x4f, 0x44, 0x00};


int main(){
	//第一次接收标志，队列总人数
	int r1_flag;
	unsigned char sum;
	//第二次接收标志，号码
	int r2_flag;
	unsigned char number;
	lcdInit();	
	delay_ms(10);
	
	initSCON();
	P2 = 0;
	P1 = 0;
	r1_flag = 0;
	r2_flag = 0;
	while(1){
		if(receive() == 200)
			r1_flag = 1;
		if(r1_flag == 1){
			r1_flag = 0;
			//P1 = receive();
			sum = receive();
			if(sum < 100)
				lcdDisplayQueueSum(0x02, sum);
			
		}
		if(receive() == 201)
			r2_flag = 1;
		if(r2_flag == 1){
			r2_flag = 0;
			//P1 = receive();
			number = receive();
			if(number < 100)
				lcdDisplayNumber(0x42, number);
		}
	}
	
	//while(1);
	
	return 0;
}