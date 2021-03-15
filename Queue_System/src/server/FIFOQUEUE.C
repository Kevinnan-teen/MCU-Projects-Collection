//////////////////////////////////////////////////////////

// 文件：FIFOQUEUE.C

//////////////////////////////////////////////////////////

#include "config.h"

//Queue Init

void QueueInit(struct FifoQueue *Queue)

{

Queue->front = Queue->rear;//初始化时队列头队列首相连

Queue->count = 0; //队列计数为0

}



// Queue In

uint8 QueueIn(struct FifoQueue *Queue,ElemType sdat) //数据进入队列

{

	if((Queue->front == Queue->rear) && (Queue->count == QueueSize))

	{ // full //判断如果队列满了

		return QueueFull; //返回队列满的标志

	}else

	{ // in

		Queue->dat[Queue->rear] = sdat;

		Queue->rear = (Queue->rear + 1) % QueueSize;

		Queue->count = Queue->count + 1;

		return QueueOperateOk;

	}

}



// Queue Out

int QueueOut(struct FifoQueue *Queue,ElemType *sdat)
{
	if((Queue->front == Queue->rear) && (Queue->count == 0))

	{ // empty

		return -1;

	}else

	{ // out

		*sdat = Queue->dat[Queue->front];

		return QueueOperateOk;

	}
}

int QueuePop(struct FifoQueue *Queue){
	if((Queue->front == Queue->rear) && (Queue->count == 0))
	{ // empty
		return -1;

	}else
	{ // out

		Queue->front = (Queue->front + 1) % QueueSize;

		Queue->count = Queue->count - 1;

		return QueueOperateOk;
	}
}


int findValue(struct FifoQueue *Queue, ElemType sdat){
	int i;
	//empty
	if((Queue->front == Queue->rear) && (Queue->count == 0)){
		return -1;
	}
	if(Queue->front <= Queue->rear){
		i = Queue->front;
		while(i <= Queue->rear){
			if(sdat == Queue->dat[i])
				return 1;
			i++;
		}
	}
	else{
		i = Queue->rear;
		while(i <= Queue->front){
			if(sdat == Queue->dat[i])
				return 1;
			i++;
		}
	}
	return -1;
}



