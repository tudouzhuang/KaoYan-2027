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
int GetTop(SqStack *S)
{
	if (S->top == -1) return 0; // 栈空
	return S->data[S->top];
}

// 括号匹配（核心）
bool bracketCheck(char str[]) {
	SqStack S;
	InitStack(&S);
	int i = 0;
	
	while (str[i] != '\0') {
		// [TODO] 1: 如果是左括号 '(', '[', '{' ，该怎么做？
		// 你的代码写在这里...
		if(str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			Push(&S,str[i]);  // 对于符合要求的左括号直接入栈
		}

		// [TODO] 2: 如果是右括号 ')', ']', '}' ，该怎么做？
		// 提示：先判空！如果为空说明右括号单身了。
		// 你的代码写在这里...
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if(S.top == -1)
				return false;
			// 这里进行判空操作
			int flag = GetTop(&S);
			// 新建flag变量读取栈中值然后进行匹配
			if((flag == '(' && str[i] == ')') ||
			   (flag == '[' && str[i] == ']') ||
			   (flag == '{' && str[i] == '}'))
				Pop(&S,&flag);
		}
		else continue;
		i++;
	}
	
	if(S.top == -1)
		return true;
	
	return false; // 替换成你真实的返回值
}

// ==========================================
// 3. 核心应用二：后缀表达式求值 (请完成核心逻辑)
// 假设表达式只包含个位正整数和 + - * /，且格式绝对合法
// ==========================================
int evaluatePostfix(char exp[]) {
	SqStack S;
	InitStack(&S);
	int i = 0;
	int tempVal, op1, op2; // op1:左操作数, op2:右操作数
	
	while (exp[i] != '\0') {
		// [TODO] 1: 如果遇到数字字符 ('0' - '9')
		// 提示：字符 '5' 怎么变成整数 5 ？ (exp[i] - '0')
		// 你的代码写在这里...
		
		// [TODO] 2: 如果遇到运算符 ('+', '-', '*', '/')
		// 提示：连续Pop出 op2 和 op1 (注意顺序!)，计算后将结果 Push 入栈
		// 你的代码写在这里...
		
		
		i++;
	}
	
	// [TODO] 3: 循环结束后，结果藏在哪里？把它Pop出来并返回。
	// 你的代码写在这里...
	return 0; // 替换成你真实的返回值
}

// ==========================================
// 4. 测试模块 (直接运行测试你的代码)
// ==========================================
int main() {
	printf("--- 括号匹配测试 ---\n");
	char str1[] = "{[()]}";
	char str2[] = "{[(])}";
	printf("str1 (应为1): %d\n", bracketCheck(str1));
	printf("str2 (应为0): %d\n", bracketCheck(str2));
	
	printf("\n--- 后缀表达式求值测试 ---\n");
	// 相当于中缀的 (3+4)*5 - 6 = 29
	char exp1[] = "34+5*6-"; 
	printf("exp1 (应为29): %d\n", evaluatePostfix(exp1));
	
	return 0;
}
