#ifndef _LCD_H
#define _LCD_H

void delay_ms(unsigned int t);

//测试LCD忙碌状态
unsigned char busyCheck();

//写命令
void lcdWriteCmd(unsigned char cmd);

//设定显示位置
void lcdPosition(unsigned char pos);

//写数据
void lcdWriteData(unsigned char dat);

//显示
void lcdDisplay(unsigned char position, unsigned char code *s);

void lcdDisplayQueueSum(unsigned char position, unsigned char num);

void lcdDisplayNumber(unsigned char position, unsigned char num);

//LCD初始化
void lcdInit();



#endif