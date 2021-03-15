#ifndef _FIFOQUEUE_H

#define _FIFOQUEUE_H

#define ElemType uint8

#define QueueSize 20 //fifo���еĴ�С

#define QueueFull 0 //fifo����0

#define QueueEmpty 1 //FIFO����1

#define QueueOperateOk 2 //���в������ ��ֵΪ2

struct FifoQueue

{

	uint16 front; //����ͷ

	uint16 rear; //����β

	uint16 count; //���м���

	ElemType dat[QueueSize];

};

//Queue Initalize

extern void QueueInit(struct FifoQueue *Queue);

// Queue In

extern uint8 QueueIn(struct FifoQueue *Queue,ElemType sdat);

// Queue Out

extern int QueueOut(struct FifoQueue *Queue,ElemType *sdat);

extern int QueuePop(struct FifoQueue *Queue);


//�鿴�������Ƿ��и�ֵ
extern int findValue(struct FifoQueue *Queue,ElemType sdat);

#endif
