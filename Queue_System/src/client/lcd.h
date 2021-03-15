#ifndef _LCD_H
#define _LCD_H

void delay_ms(unsigned int t);

//����LCDæµ״̬
unsigned char busyCheck();

//д����
void lcdWriteCmd(unsigned char cmd);

//�趨��ʾλ��
void lcdPosition(unsigned char pos);

//д����
void lcdWriteData(unsigned char dat);

//��ʾ
void lcdDisplay(unsigned char position, unsigned char code *s);

void lcdDisplayQueueSum(unsigned char position, unsigned char num);

void lcdDisplayNumber(unsigned char position, unsigned char num);

//LCD��ʼ��
void lcdInit();



#endif