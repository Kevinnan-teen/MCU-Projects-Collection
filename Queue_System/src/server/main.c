#include <STC/STC89C5xRC.h>
#include <intrins.h>


#include "config.h"
#include "server_uart.h"

typedef unsigned char uchar;

sbit led_0 = P1^3;
sbit led_1 = P1^4;
sbit led_2 = P1^5;

sbit busy = P1^0;
sbit dat  = P1^1;
sbit rest = P1^2;





void delay_ms(unsigned int t)                      //ms延时程序                                                                      
{                                                                                                                                       
    unsigned char i;                                                                                                                 
     unsigned int x;                                                                                                                  
     x=t;                                                                                                                              
     while(x--)                                                                                                                        
     {                                                                                                                                          
             for(i=0;i<113;i++);                                                                                                              
     }                                                                                                                                           
}   

void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1s()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}

                                                                                                                                     
sbit R1 = P2^0;
sbit R2 = P2^1;
sbit R3 = P2^2;
sbit R4 = P2^3;

sbit C1 = P2^4;
sbit C2 = P2^5;
sbit C3 = P2^6;

sbit DULA = P1^6;
sbit WELA = P1^7;

int scanKey3(){
	R1=0,R2=1,R3=1,R4=1;
	if(C1==0)
		return 1;
	if(C2==0)
		return 2;
	if(C3==0)
		return 3;
	
	R1=1,R2=0,R3=1,R4=1;
	if(C1==0)
		return 4;
	if(C2==0)
		return 5;
	if(C3==0)
		return 6;
	
	R1=1,R2=1,R3=0,R4=1;
	if(C1==0)
		return 7;
	if(C2==0)
		return 8;
	if(C3==0)
		return 9;
	
	R1=1,R2=1,R3=1,R4=0;
	if(C1==0)
		return -1;
	if(C2==0)
		return 0;
	if(C3==0)
		return 10;
	
	return -2;
}


//共阴数码管
uchar code table[] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};	// 0~9

void displayTopQueueNumber(int select_number){	
	uchar position = 0XBF;
	int z, x;
	if(select_number == -1)
		return;
	z = select_number / 10;
	x = select_number % 10;
	
	P0 = position;
	WELA = 1;
	WELA = 0;
	P0 = table[z];
	DULA = 1;
	DULA = 0;
	delay_ms(2);
	
	position = _crol_(position, 1);
	P0 = position;
	WELA = 1;
	WELA = 0;
	P0 = table[x];
	DULA = 1;
	DULA = 0;
	delay_ms(2);
}


void displaySelectNumber(int select_number){	
	uchar position = 0XFE;
	int z, x;
	if(select_number == -1)
		return;
	z = select_number / 10;
	x = select_number % 10;
	
	P0 = position;
	WELA = 1;
	WELA = 0;
	P0 = table[z];
	DULA = 1;
	DULA = 0;
	delay_ms(2);
	
	position = _crol_(position, 1);
	P0 = position;
	WELA = 1;
	WELA = 0;
	P0 = table[x];
	DULA = 1;
	DULA = 0;
	delay_ms(2);
}

void displayTimes(int times){	
	uchar position = 0XF7;
	DULA = 0;
	P0 = position;
	WELA = 1;
	WELA = 0;
	P0 = table[times];
	DULA = 1;
	DULA = 0;
	delay_ms(2);
}


void music(int z){
	rest = 1;
	delay_ms(2);
	rest = 0;	
	delay_ms(2);
	while(z > 0){
		dat = 1;
		delay_ms(1);
		dat = 0;
		delay_ms(1);
		z--;
	}
}

void sound(int select_number){
	int front = select_number / 10;
	int end = select_number % 10;
	switch(front){
		case 0:
			music(1);
			//Delay1s();
			break;
		case 1:
			music(11);
			//Delay1s();
			break;
		default:
			music(front+1);
			//Delay1s();
			music(11);
			//Delay1s();
			break;
	}
	music(end+1);
	//Delay1s();
}

//定时器0中断初始化
void Time0Init(){
	//TMOD = 0X01;	//在串口初始化时初始化了
	TH0 = 0X4C;
	TL0 = 0X00;
	ET0 = 1;
	TR0 = 1;
	EA  = 1;
}


int main(){
	int v;
	//按键选择的号
	int select_number;
	//出队的号
	int output_number;
	int sn;
	//按键次数
	int times;
	
	int dis;
	
	uchar send_p;
	
	int one_second_times;
	int sound_times;
	//只响一次
	int only_sound_once;
	
	int sound_1_once;
	int sound_2_once;
	int sound_3_once;
	
	//将数据放在RAM
	struct FifoQueue data MyQueue;
	ElemType sh;
	QueueInit(&MyQueue);
	sh = -1;
	dis = -1;
	
	one_second_times = 0;
	sound_times = 0;
	only_sound_once = 1;
	sound_1_once = 0;
	sound_2_once = 0;
	sound_3_once = 0;
	
	
	
	
	//初始化串口
	initSCON();
	
	//初始化定时器
	Time0Init();
	
	led_0 = 0;
	led_1 = 0;
	led_2 = 0;
	
	//P0 = 0XFF;
	output_number = -1;
	select_number = -1;
	times = 0;	
	
	while(1){
		if(TF0 == 1){
			TH0 = 0X4C;
			TL0 = 0X00;
			if(only_sound_once == 0)
				one_second_times++;
			TF0 = 0;
		}
		v = scanKey3();
		if(v==0 || v==1 || v==2 || v==3 || v==4 ||v==5 || v==6 || v==7 || v==8 || v==9 || v==10 || v==-1){
			//led_0 = 1;
			//ToDo:	此处延时应该使用定时器延时，即当定时器中的变量为某个值时，led变色
			delay_ms(500);
			//led_0 = 0;
			//displayTimes(v);
		}
		//按键被按下
		if(v == -1){
			//响		
			QueueOut(&MyQueue,&sh);		
			output_number = sh;
			QueuePop(&MyQueue);
			only_sound_once = 0;
			sound_1_once = 0;
			sound_2_once = 0;
			sound_3_once = 0;			
			
		}
		else if(v != -2){
			switch(times){
			case 0:
				times++;
				sn = v*10;
				break;
			case 1:
				times++;
				sn = sn + v;
				break;
			case 2:
				//ToDo:第三次按下，如果不是#键，即确定键，则第三次不算。
				if(v == 10){
					//如果不在队列中，才入队
					if(findValue(&MyQueue, sn) == -1){
						select_number = sn;
						QueueIn(&MyQueue, select_number);
					}
				}
				times=0;
				sn = 0;
				break;			
			}
		}	
		
		if(only_sound_once == 0){
			if(output_number / 10 == 0){
				// 00 -- 09
				if(sound_times == 0){
					if(sound_1_once == 0){
						led_0 = ~led_0;
						music(1);
						sound_1_once = 1;
					}				
				}else if(sound_times == 1){
					if(sound_2_once == 0){
						led_1 = ~led_1;
						music((output_number % 10) + 1);
						sound_2_once = 1;
						//关
						sound_times = 0;
						only_sound_once = 1;
					}
				}
			}else if(output_number == 10){
				// 10
				led_0 = ~led_0;
				music(11);
				//关
				sound_times = 0;
				only_sound_once = 1;
			}else if(output_number / 10 == 1){
				// 11 -- 19
				if(sound_times == 0){
					if(sound_1_once == 0){
						led_0 = ~led_0;
						//music((select_number / 10) + 1);
						music(11);
						sound_1_once = 1;
					}				
				}else if(sound_times == 1){
					if(sound_2_once == 0){
						led_1 = ~led_1;
						music((output_number % 10) + 1);
						sound_2_once = 1;
						//关
						sound_times = 0;
						only_sound_once = 1;
					}
				}
			}else if(output_number % 10 == 0){
				// 20 30 40 ... 90
				if(sound_times == 0){
					if(sound_1_once == 0){
						led_0 = ~led_0;
						music((output_number / 10) + 1);
						sound_1_once = 1;
					}				
				}else if(sound_times == 1){
					if(sound_2_once == 0){
						led_1 = ~led_1;
						music(11);
						sound_2_once = 1;
						//关
						sound_times = 0;
						only_sound_once = 1;
					}
				}
			}else{
				// 21 -- 29, 31 -- 39 ... 91 -- 99
				if(sound_times == 0){
					if(sound_1_once == 0){
						led_0 = ~led_0;
						music((output_number / 10) + 1);
						//music(1);
						sound_1_once = 1;
					}				
				}else if(sound_times == 1){
					if(sound_2_once == 0){
						led_1 = ~led_1;
						music(11);
						sound_2_once = 1;
					}
				}else if(sound_times == 2){
					if(sound_3_once == 0){					
						music((output_number % 10) + 1);
						//music(3);
						led_2 = ~led_2;
						sound_3_once = 1;
					}
					//关
					sound_times = 0;
					only_sound_once = 1;
				}
			}
		}
		
		
		
		if(one_second_times == 15){
			one_second_times = 0;
			sound_times++;
			//led_0 = 1;
		}
		
		
		if(select_number != -1)
			displaySelectNumber(select_number);
		
		if(output_number != -1)
			displayTopQueueNumber(output_number);
		
		displayTimes(MyQueue.count);
		//displaySelectNumber(select_number);
		
		send_p = 200;
		send(send_p);
		send_p = MyQueue.count;
		send(send_p);
		
		send_p = 201;
		send(send_p);
		send_p = select_number;
		send(send_p);
			
//		if(myCircularQueueFront(mq) == -1)
//			displayTimes(2);
//		else
//			displayTimes(1);
			
	}
	return 0;
}

