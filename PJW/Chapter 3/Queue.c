#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct
{
	int data[MAXSIZE];
	int front;
	int rear;
} SqQueue;


/* 初始化队列 */
void InitQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	// TODO: 初始化队头和队尾
}


/* 判断队列是否为空 */
int IsEmpty(SqQueue *Q)
{
	if(Q->front == Q->rear)
		return 1;
	else return 0;
	// TODO: 判断是否为空
}


/* 判断队列是否已满 */
int IsFull(SqQueue *Q)
{
	if((Q->rear + 1) % MAXSIZE == Q->front)
		return 1;
	else return 0;
	// TODO: 判断循环队列是否满
}


/* 入队 */
int EnQueue(SqQueue *Q, int x)
{
	// 1 判断是否已满
	if(IsFull(Q))
	{
		printf("队列已满\n");
		return 0;
	}
	
	// 2 插入元素
	Q->data[Q->rear] = x;
	// TODO
	
	// 3 rear移动
	Q->rear = (Q->rear + 1) % MAXSIZE;
	// TODO
	
	return 1;
}


/* 出队 */
int DeQueue(SqQueue *Q, int *x)
{
	// 1 判断是否为空
	if(IsEmpty(Q))
	{
		printf("队列为空\n");
		return 0;
	}
	
	// 2 取出队头元素
	*(x) = Q->data[Q->front];
	// TODO
	
	// 3 front移动
	Q->front = (Q->front + 1) % MAXSIZE;
	// TODO
	
	return 1;
}


/* 获取队头元素（不删除） */
int GetHead(SqQueue *Q, int *x)
{
	if(IsEmpty(Q))
	{
		printf("队列为空\n");
		return 0;
	}
	
	// TODO: 读取队头元素
	*(x) = Q->data[Q->front];
	return 1;
}


/* 打印队列 */
void PrintQueue(SqQueue *Q)
{
	int i = Q->front;
	
	printf("队列元素: ");
	
	while(i != Q->rear)
	{
		printf("%d ", Q->data[i]);
		i = (i+1)%MAXSIZE;
		// TODO: 循环移动 i
	}
	
	printf("\n");
}


int main()
{
	SqQueue Q;
	
	InitQueue(&Q);
	
	EnQueue(&Q,10);
	EnQueue(&Q,20);
	EnQueue(&Q,30);
	EnQueue(&Q,40);
	
	PrintQueue(&Q);
	
	int x;
	
	DeQueue(&Q,&x);
	printf("出队元素: %d\n",x);
	
	PrintQueue(&Q);
	
	GetHead(&Q,&x);
	printf("当前队头: %d\n",x);
	
	return 0;
}
