#ifndef _FIFOQUEUE_H

#define _FIFOQUEUE_H

#define ElemType uint8

#define QueueSize 20 //fifo队列的大小

#define QueueFull 0 //fifo满置0

#define QueueEmpty 1 //FIFO空置1

#define QueueOperateOk 2 //队列操作完成 赋值为2

struct FifoQueue

{

	uint16 front; //队列头

	uint16 rear; //队列尾

	uint16 count; //队列计数

	ElemType dat[QueueSize];

};

//Queue Initalize

extern void QueueInit(struct FifoQueue *Queue);

// Queue In

extern uint8 QueueIn(struct FifoQueue *Queue,ElemType sdat);

// Queue Out

extern int QueueOut(struct FifoQueue *Queue,ElemType *sdat);

extern int QueuePop(struct FifoQueue *Queue);


//查看队列中是否有该值
extern int findValue(struct FifoQueue *Queue,ElemType sdat);

#endif
