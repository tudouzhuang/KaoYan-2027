#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

// ==========================================
// 1. 基础数据结构定义 (408 严蔚敏版标准写法)
// ==========================================
typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// ==========================================
// 2. 辅助工具区 (已为你搭好，直接调用即可)
// ==========================================
// --- 简易队列 (供层序遍历、判断完全二叉树使用) ---
typedef struct {
	BiTree data[MAXSIZE];
	int front, rear;
} Queue;
void InitQueue(Queue *Q) { Q->front = Q->rear = 0; }
bool IsEmpty(Queue Q) { return Q.front == Q.rear; }
void EnQueue(Queue *Q, BiTree x) { Q->data[Q->rear++] = x; }
BiTree DeQueue(Queue *Q) { return Q->data[Q->front++]; }

// --- 简易栈 (供非递归遍历、寻找祖先路径使用) ---
typedef struct {
	BiTree data[MAXSIZE];
	int top;
} Stack;
void InitStack(Stack *S) { S->top = -1; }
bool StackEmpty(Stack S) { return S.top == -1; }
void Push(Stack *S, BiTree x) { S->data[++S->top] = x; }
BiTree Pop(Stack *S) { return S->data[S->top--]; }

// --- 构造测试树 ---
// 结构:       1
//           /   \
//          2     3
//         / \   / \
//        4   5 6   7
BiTNode* CreateNode(int val) {
	BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
	node->data = val; node->lchild = node->rchild = NULL;
	return node;
}
BiTree CreateTestTree() {
	BiTree n1 = CreateNode(1); BiTree n2 = CreateNode(2); BiTree n3 = CreateNode(3);
	BiTree n4 = CreateNode(4); BiTree n5 = CreateNode(5); BiTree n6 = CreateNode(6);
	BiTree n7 = CreateNode(7);
	n1->lchild = n2; n1->rchild = n3;
	n2->lchild = n4; n2->rchild = n5;
	n3->lchild = n6; n3->rchild = n7;
	return n1;
}

// ==========================================
// 🌟 第一阶梯：遍历与属性 (基础中的基础)
// ==========================================

// [TODO 1] 中序遍历 (递归)
// 左根右
void InOrder(BiTree T) {
	// 你的代码写在这里...
	if (T == NULL) {
		return; 
	}
	if(T->lchild != NULL) InOrder(T->lchild);
	printf("%d ",T->data);
	if(T->rchild != NULL) InOrder(T->rchild);
}

// [TODO 2] 层序遍历 (使用上面提供的 Queue)
void LevelOrder(BiTree T) {
	// 你的代码写在这里...
	Queue Q;
	InitQueue(&Q);
	BiTree p;
	EnQueue(&Q,T);
	while(!IsEmpty(Q)){
		p = DeQueue(&Q);
		printf("%d ",p->data);
		if(p->lchild!=NULL) EnQueue(&Q,p->lchild);
		if(p->rchild!=NULL) EnQueue(&Q,p->rchild);
	}
}

// [TODO 3] 求二叉树的高度
int TreeDepth(BiTree T) {
	if (T == NULL) return 0; // 1. 绝对防御
	
	int leftDepth = TreeDepth(T->lchild);  // 2. 探底左边
	int rightDepth = TreeDepth(T->rchild); // 3. 探底右边
	
	return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// [TODO 4] 统计度为 2 的结点个数 (双分支结点)
// 提示：左孩子不空 且 右孩子不空
int NodeCountDegree2(BiTree T) {
	// 你的代码写在这里...
	if(T == NULL)
		return 0;
	if(T->lchild != NULL && T->rchild != NULL)
		return 1+NodeCountDegree2(T->lchild)+NodeCountDegree2(T->rchild);
	else if(T->lchild == NULL && T->rchild != NULL)
		return 1+NodeCountDegree2(T->rchild);
	else if(T->lchild != NULL && T->rchild == NULL)
		return 1+NodeCountDegree2(T->lchild);		
	return 0;
}

// ==========================================
// 🌟 第二阶梯：魔改递归 (大题常客)
// ==========================================

// [TODO 5] 二叉树的镜像翻转
// 提示：把每个结点的左右孩子指针交换即可，递归进行。
void MirrorTree(BiTree T) {
	// 你的代码写在这里...
	if(T == NULL)
		return;
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;
	MirrorTree(T->lchild);
	MirrorTree(T->rchild);
}

// [TODO 6] 判断一棵树是否是完全二叉树
// 提示：利用层序遍历！空指针也入队。一旦出队遇到空指针，检查队列后面是否还有非空结点。
// 如果有，则不是完全二叉树；如果全是空，则是。
bool IsCompleteTree(BiTree T) {
	if (T == NULL) return true; // 空树也是完全二叉树
	
	Queue Q;
	InitQueue(&Q);
	EnQueue(&Q, T);
	
	int flag = 0; // 0 表示没遇到过 NULL，1 表示已经遇到过 NULL 了
	BiTree p;
	
	while (!IsEmpty(Q)) {
		p = DeQueue(&Q);
		
		if (p != NULL) {
			if (flag == 1) {
				return false; 
			}
			EnQueue(&Q, p->lchild);
			EnQueue(&Q, p->rchild);
		} else {
			flag = 1; // 拉响警报：从现在起，后面出队的绝对不能再有“真结点”了！
		}
	}
	return true; 
}

// ==========================================
// 🌟 第三阶梯：终极大招 (压轴级别)
// ==========================================

// [TODO 7] 打印值为 x 的结点的祖先路径
// 提示 1 (递归法)：bool 返回值，若当前结点或子树找到 x，则打印当前结点并返回 true。
// 提示 2 (非递归法)：使用后序遍历的非递归写法，栈里的元素就是祖先路径！
bool PrintAncestors(BiTree T, int x) {
	// 你的代码写在这里...
	return false;
}

// [TODO 8] 二叉树的构造 (先序 + 中序)
// pre[] 是先序序列，in[] 是中序序列，l1, r1 是先序的左右边界，l2, r2 是中序的左右边界
// 提示：pre[l1] 是根！在中序里找到根的位置，划分左右子树，递归构造。
BiTree BuildTree(int pre[], int l1, int r1, int in[], int l2, int r2) {
	// 你的代码写在这里...
	return NULL;
}

// [TODO 9] 判断是否为二叉排序树 (BST)
// 提示：利用中序遍历！BST 的中序遍历序列必定是“严格递增”的。
// 可以用一个全局变量或指针记录前驱结点的值进行比较。
int preValue = -9999; // 辅助变量
bool IsBST(BiTree T) {
	// 你的代码写在这里...
	return false;
}

// ==========================================
// 测试模块
// ==========================================
int main() {
	BiTree root = CreateTestTree();
	
	printf("1. 中序遍历 (应为 4 2 5 1 6 3 7): ");
	InOrder(root); printf("\n");
	
	printf("2. 层序遍历 (应为 1 2 3 4 5 6 7): ");
	LevelOrder(root); printf("\n");
	
	printf("3. 树的高度 (应为 3): %d\n", TreeDepth(root));
	
	printf("4. 度为2的结点数 (应为 3): %d\n", NodeCountDegree2(root));
	
	printf("5. 是否完全二叉树 (应为 1): %d\n", IsCompleteTree(root));
	
	printf("6. 结点 5 的祖先 (应为 2 1): ");
	PrintAncestors(root, 5); printf("\n");
	
	// 测试 BST
	BiTree bstRoot = CreateNode(5);
	bstRoot->lchild = CreateNode(3); bstRoot->rchild = CreateNode(7);
	printf("7. IsBST 测试 (应为 1): %d\n", IsBST(bstRoot));
	
	// 测试树的构造
	int pre[] = {1, 2, 4, 5, 3, 6, 7};
	int in[]  = {4, 2, 5, 1, 6, 3, 7};
	BiTree newTree = BuildTree(pre, 0, 6, in, 0, 6);
	printf("8. 构造树测试(层序遍历新树,应为 1 2 3 4 5 6 7): ");
	LevelOrder(newTree); printf("\n");
	
	return 0;
}
