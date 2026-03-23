#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 50

// ==========================================
// 1. 基础数据结构定义 (已为你搭好)
// ==========================================
typedef struct {
	int data[MAXSIZE]; // 为了通用，这里用int。存字符时(括号)，利用ASCII码隐式转换
	int top;           // 栈顶指针
} SqStack;

// 初始化栈
void InitStack(SqStack *S) {
	S->top = -1; 
}

// 判空
bool StackEmpty(SqStack S) {
	return S.top == -1;
}

// 入栈
bool Push(SqStack *S, int x) {
	if (S->top == MAXSIZE - 1) return false; // 栈满
	S->data[++(S->top)] = x;
	return true;
}

// 出栈
bool Pop(SqStack *S, int *x) {
	if (S->top == -1) return false; // 栈空
	*x = S->data[(S->top)--];
	return true;
}

// 读取栈顶
int GetTop(SqStack *S) {
	if (S->top == -1) return 0; // 栈空
	return S->data[S->top];
}

// ==========================================
// 2. 核心应用一：括号匹配
// ==========================================
bool bracketCheck(char str[]) {
	SqStack S;
	InitStack(&S);
	int i = 0;
	
	while (str[i] != '\0') {
		if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
			Push(&S,str[i]);  
		}
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}') {
			if(S.top == -1)
				return false;
			int flag = GetTop(&S);
			if((flag == '(' && str[i] == ')') ||
			   (flag == '[' && str[i] == ']') ||
			   (flag == '{' && str[i] == '}'))
				Pop(&S,&flag);
		}
		i++;
	}
	
	if(S.top == -1)
		return true;
	
	return false; 
}

// ==========================================
// 3. 核心应用二：后缀表达式求值 
// ==========================================
int evaluatePostfix(char exp[]) {
	SqStack S;
	InitStack(&S);
	int i = 0;
	int op1, op2; 
	
	while (exp[i] != '\0') {
		if(exp[i] >= '0' && exp[i] <= '9') {
			Push(&S,exp[i]-'0');
		}
		if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
			Pop(&S,&op2);
			Pop(&S,&op1);
			switch(exp[i]) {
				case '+': Push(&S, op1 + op2); break; 
				case '-': Push(&S, op1 - op2); break;
				case '*': Push(&S, op1 * op2); break;
				case '/': Push(&S, op1 / op2); break;
				default: break; 
			}
		}
		i++;
	}
	
	int result;
	Pop(&S,&result);
	return result; 
}

// ==========================================
// 🌟 核心应用三：中缀表达式转后缀表达式 (你的新战场)
// ==========================================

// 辅助函数：获取运算符的优先级
int getPriority(char op) {
	if (op == '*' || op == '/') return 2;
	if (op == '+' || op == '-') return 1;
	return 0; // 遇到左括号或其他字符，优先级视为最低
}

// 转换主函数
// infix: 传入的中缀表达式字符串
// postfix: 用来存放生成的后缀表达式的空数组
void infixToPostfix(char infix[], char postfix[]) {
	SqStack S;
	InitStack(&S);
	int i = 0; // 用于遍历中缀表达式 infix
	int k = 0; // 用于给后缀表达式 postfix 赋值的位置指针
	
	while (infix[i] != '\0') {
		// [TODO] 1: 如果是数字字符 ('0' - '9')，直接存入 postfix
		// 提示：postfix[k++] = infix[i];
		// 你的代码写在这里...
		if(infix[i] >= '0' && infix[i] <= '9')
			postfix[k++] = infix[i];
		
		// [TODO] 2: 如果是左括号 '('，无脑入栈
		// 你的代码写在这里...
		if(infix[i] == '(')
			Push(&S,infix[i]);
		
		
		// [TODO] 3: 如果是右括号 ')'，不断出栈并存入 postfix，直到遇到左括号 '('
		// 提示：用 while 循环，条件是 !StackEmpty(S) 且 GetTop(&S) != '('
		// 提示：循环结束后，记得再 Pop 一次，把那个 '(' 弹出来扔掉！
		// 你的代码写在这里...
		if(infix[i] == ')')
		{
			int temp;
			Pop(&S,&temp);
			while(temp != '(' && !StackEmpty(S))  //为左括号且不为空，其实这里必要性不是很大，默认表达式是正确的
			{
				postfix[k++] = temp;
				Pop(&S,&temp);
			}
			// 此时应该是temp == '('
		}
		
		
		// [TODO] 4: 如果是运算符 ('+', '-', '*', '/')
		// 提示：用 while 循环。只要栈不空，且 GetTop(&S) != '('，
		//       且 getPriority(GetTop(&S)) >= getPriority(infix[i])
		//       就把栈顶元素 Pop 出来存入 postfix[k++]。
		// 提示：清理完比自己强或一样强的对手后，把自己 Push 进栈。
		// 你的代码写在这里...
		if(getPriority(infix[i]) > 0) //只有在运算符的时候>0
		{
			while(getPriority(infix[i]) <= getPriority(GetTop(&S)) && !StackEmpty(S)) //此时判断条件为优先级小于等于栈顶
			{
				int temp;
				Pop(&S,&temp);
				postfix[k++] = temp;
			}
			Push(&S,infix[i]);
		}
		
		
		i++;
	}
	
	// [TODO] 5: 遍历结束，把栈里剩下的所有运算符全部 Pop 并存入 postfix
	// 提示：用 while 循环直到栈空。
	// 提示：最后一定要加上后缀表达式的字符串结束符：postfix[k] = '\0';
	// 你的代码写在这里...
	while(!StackEmpty(S))
	{
		int temp;
		Pop(&S,&temp);
		postfix[k++] = temp;
	}
	postfix[k] = '\0';
	
}

// ==========================================
// 4. 测试模块 
// ==========================================
int main() {
	// 前面的测试先注释掉，专注看新代码
	/*
	printf("--- 括号匹配测试 ---\n");
	char str1[] = "{[()]}";
	char str2[] = "{[(])}";
	printf("str1 (应为1): %d\n", bracketCheck(str1));
	printf("str2 (应为0): %d\n", bracketCheck(str2));
	
	printf("\n--- 后缀表达式求值测试 ---\n");
	char exp1[] = "34+5*6-"; 
	printf("exp1 (应为29): %d\n", evaluatePostfix(exp1));
	*/
	
	printf("\n--- 中缀转后缀测试 ---\n");
	// 相当于手工推导: 3 + 4 * 5 - 6 -> 3 4 5 * + 6 -
	char infix1[] = "3+4*5-6";
	char postfix1[50]; // 准备一个空数组存放结果
	
	infixToPostfix(infix1, postfix1);
	
	printf("中缀表达式: %s\n", infix1);
	printf("后缀表达式: %s\n", postfix1);
	printf("(标准答案应为: 345*+6-)\n");
	
	// 你还可以结合你刚写的求值函数，来个终极一条龙测试！
	// printf("\n终极测试求值结果: %d\n", evaluatePostfix(postfix1)); // 应该等于 17
	
	return 0;
}
