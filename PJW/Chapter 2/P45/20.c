#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node* next;
}NODE;
// 这里按照通用设置设置一个带头节点的默认链表,长度为10

NODE* InitNode(){
	int x = 1;
	NODE* L=(NODE*)malloc(sizeof(NODE));  // 创建头节点
	NODE *s,*r=L;
	while(x!=10)
	{
		s = (NODE *)malloc(sizeof(NODE));
		s->data = x;
		r->next = s;
		r = s;
		x++;
	}
	r->next = NULL;
	return L;
}

void PrintNode(NODE *n)  // 输出链表,默认有头节点,输入参数为头指针
{
	int count = 0;
	NODE *p=n->next;  //头指针->头节点->头节点指向的第一个节点
	if(p == NULL)
	{
		printf("该链表为空\n");
	}
	while(p != NULL)
	{
		printf("%d ",p->data);
		p = p->next;
		count ++;
	}
	printf("\n该链表的长度为: %d",count);
	return;
}



int main()
{
	NODE *head = InitNode();
	PrintNode(head);
	return 0;
}
