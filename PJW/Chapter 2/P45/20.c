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

NODE* FindCenterCut(NODE *n) {
	NODE *p = n, *q = n; // 从头结点开始
	while (p != NULL && p->next != NULL) {
		p = p->next->next; // 快指针走两步
		q = q->next;       // 慢指针走一步
	}
	NODE *flag = q;
	
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

NODE *MergeTwoNode(NODE *a, NODE *b) //默认都不带头节点
{
	// 1. 边界防御：如果其中一个为空，直接返回另一个
	if (a == NULL) return b;
	if (b == NULL) return a;
	
	NODE *head = a;        // 保存返回的头指针
	NODE *p = a->next;     // a 链表待合并的下一个节点
	NODE *q = b;           // b 链表待合并的当前节点
	NODE *merged = a;      // 尾指针，始终指向合并链表的最后
	
	// 2. 核心交错合并逻辑
	while (p != NULL && q != NULL) 
	{
		// 先接 b 链表的节点 (q)
		merged->next = q;
		q = q->next;
		merged = merged->next;
		
		// 再接 a 链表的节点 (p)
		merged->next = p;
		p = p->next;
		merged = merged->next;
	}
	
	// 3. 处理剩余的尾巴（哪个没空就接哪个）
	if (p != NULL) {
		merged->next = p;
	} else if (q != NULL) {
		merged->next = q;
	}
	
	// 4. 返回正确的头指针
	return head;
}

// 核心思想是找到中间的节点,然后倒序后面的链表,然后依次插入
int main()
{
	NODE *head = InitNode();
	NODE *test = InitNode();
	PrintNode(head);
	ReverseNode(head);
	PrintNode(head);
	test = MergeTwoNode(head,test->next);
	PrintNode(test);
	printf("\n\n\n\n");
	printf("---------- 408 真题模拟开始 ----------\n");
	NODE *answer = InitNode();
	printf("原链表: ");
	PrintNode(answer);
	
	// 1. 找中点
	NODE *mid = FindCenter(answer); // q 会停在前半段的最后一个节点
	
	// 2. 关键：保存后半段并断链
	// 因为你的 ReverseNode 需要一个【头节点】，所以我们给后半段专门造一个临时头节点
	NODE *half_head = (NODE*)malloc(sizeof(NODE)); 
	half_head->next = mid->next; // 临时头节点接上 6, 7, 8, 9
	mid->next = NULL;            // 斩断前半段！answer 现在是 头->1->2->3->4->5->NULL
	
	// 3. 逆置后半段
	ReverseNode(half_head);      // half_head 现在是 头->9->8->7->6->NULL
	
	// 4. 合并
	// answer 传入带着头节点，half_head->next 是后半段的第一个真实节点(9)
	answer = MergeTwoNode(answer, half_head->next);
	
	printf("处理后: ");
	PrintNode(answer);
	
	free(half_head); // 用完了别忘了释放临时头节点
}
