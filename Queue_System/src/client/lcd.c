#include "lcd.h"

#include <reg52.h>
#include <intrins.h>

sbit RS = P2^2;
sbit RW = P2^1;
sbit EP = P2^0;

unsigned char code num_table[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
unsigned char code queuesum_table[] = {0x71, 0x75, 0x65, 0x75, 0x65, 0xa0, 0x73, 0x75, 0x6d, 0x3a, 0x00};
unsigned char code number_table[] = {0x6e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x3a, 0x00};

void delay_ms(unsigned int t)                      //ms��ʱ����                                                                      
{                                                                                                                                       
    unsigned char i;                                                                                                                 
     unsigned int x;                                                                                                                  
     x=t;                                                                                                                              
     while(x--)                                                                                                                        
     {                                                                                                                                          
             for(i=0;i<113;i++);                                                                                                              
     }                                                                                                                                           
} 


unsigned char busyCheck(){
	unsigned char LCD_status;
	RS = 0;
	RW = 1;
	EP = 1;	//EPΪʹ�ܶˣ���EP�ɸߵ�ƽ�����͵�ƽʱ��Һ����д�����ݡ�
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
	LCD_status = P0 & 0X80;	//���λD7Ϊ1����ʾæ�����ܽ������ݣ� ���λD7Ϊ0����ʾ���У��������ݣ�
	EP = 0;
	return LCD_status;	
}

void lcdPosition(unsigned char pos){
	lcdWriteCmd(pos | 0X80);
}

void lcdWriteCmd(unsigned char cmd){
	while(busyCheck());
	RS = 0;
	RW = 0;
	EP = 0;
	_nop_();
	_nop_();
	P0 = cmd;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EP = 1;		//EP�½��أ�д������
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EP = 0;
}

void lcdWriteData(unsigned char dat){
	while(busyCheck());
	RS = 1;
	RW = 0;
	EP = 0;
	P0 = dat;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EP = 0;
}


void lcdDisplay(unsigned char position, unsigned char code *s){
	unsigned char i;
	lcdPosition(position);
	i = 0;
	while(s[i] != 0x00){
		//dChar(s[i]);
		lcdWriteData(s[i]);
		while(busyCheck());
		i++;
	}
}


void lcdDisplayQueueSum(unsigned char position, unsigned char num){
	unsigned char s[3];
	unsigned char i;
	lcdPosition(position);
	s[0] = num_table[num / 10];
	s[1] = num_table[num % 10];
	s[2] = 0x00;
	i = 0;
	while(queuesum_table[i] != 0x00){
		//dChar(s[i]);
		lcdWriteData(queuesum_table[i]);
		while(busyCheck());
		i++;
	}
	i = 0;
	while(s[i] != 0x00){
		//dChar(s[i]);
		lcdWriteData(s[i]);
		while(busyCheck());
		i++;
	}
}

void lcdDisplayNumber(unsigned char position, unsigned char num){
	unsigned char s[3];
	unsigned char i;
	lcdPosition(position);
	s[0] = num_table[num / 10];
	s[1] = num_table[num % 10];
	s[2] = 0x00;
	i = 0;
	while(number_table[i] != 0x00){
		//dChar(s[i]);
		lcdWriteData(number_table[i]);
		while(busyCheck());
		i++;
	}
	i = 0;
	while(s[i] != 0x00){
		//dChar(s[i]);
		lcdWriteData(s[i]);
		while(busyCheck());
		i++;
	}
}

void lcdInit(){
	//�����趨��
	//0x3c : 8λ���ߣ����У�5x10����
	//0x38 �� 8λ���ߣ����У�5x7����
	//0x34�� 8λ���ߣ�һ�У�
	lcdWriteCmd(0x3c);
	delay_ms(1);
	//��ʾ���ؿ��ƣ�0x0c����ʾ���ܿ����޹��
	lcdWriteCmd(0x0c);	
	delay_ms(1);
	//���õ�һ�п�ʼλ��
	lcdWriteCmd(0x06);
	delay_ms(1);
	lcdWriteCmd(0x01);
	delay_ms(1);
}