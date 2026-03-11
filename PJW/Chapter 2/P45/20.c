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

NODE* FindCenter(NODE *n) {
	NODE *p = n, *q = n; // 从头结点开始
	while (p != NULL && p->next != NULL) {
		p = p->next->next; // 快指针走两步
		q = q->next;       // 慢指针走一步
	}
	return q; // 奇数个返回中心，偶数个返回前半部分最后一个
}

void ReverseNode(NODE *h) { 
	if (h == NULL || h->next == NULL) return;
	NODE *p = h->next, *q;
	h->next = NULL; // 先把头断开
	while (p != NULL) {
		q = p->next;    // 保存后继
		p->next = h->next; // 头插
		h->next = p;
		p = q;
	}
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
	printf("\n该链表的长度为: %d\n",count);
	return;
}


// 核心思想是找到中间的节点,然后倒序后面的链表,然后依次插入
int main()
{
	NODE *head = InitNode();
	PrintNode(head);
	ReverseNode(head);
	PrintNode(head);
	return 0;
}
