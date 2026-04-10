#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 255

// ==========================================
// 1. 基础数据结构定义 (注意：下标从 1 开始使用！)
// ==========================================
typedef struct {
	char ch[MAXLEN + 1]; // 分配 MAXLEN+1 的空间，ch[0] 废弃不用
	int length;          // 串的实际长度
} SString;

// 初始化串（已为你写好，自动将传入的普通C字符串转为从 1 开始的 SString）
void InitString(SString *S, char *str) {
	int i = 1; // 强制从 1 开始存
	int j = 0; // 遍历普通字符串的指针
	while (str[j] != '\0' && i <= MAXLEN) {
		S->ch[i] = str[j];
		i++;
		j++;
	}
	S->length = j;
}

// ==========================================
// 🌟 核心操作一：求模式串的 next 数组 (极度烧脑，请细品)
// ==========================================
void get_next(SString T, int next[]) {
	int i=1,j=0;
	next[1] = 0;
	while(i < T.length)
	{
		if(j == 0 || T.ch[i] == T.ch[j])
		{
			j++;i++;
			next[i] = j;
		}
		else{
			j = next[j];
		}
	}
}

// ==========================================
// 🌟 核心操作二：由 next 数组优化出 nextval 数组
// ==========================================
// 这就是把你刚才做的“看当前字符和回退位置的字符相不相等”的口诀翻译成代码
void get_nextval(SString T, int nextval[]) {
	// 铁律：第一个字符的 nextval 无脑为 0
	nextval[1] = 0;
	int i = 1,j = 0;
	
	while(i < T.length)
	{
		if(j == 0 || T.ch[i] == T.ch[j])
		{
			i++;j++;
			nextval[i] = j;
			if(T.ch[i] != T.ch[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else{
			j = nextval[j];
		}
	}
	
}

// ==========================================
// 🌟 核心操作三：KMP 模式匹配主程序
// ==========================================
// 返回子串 T 在主串 S 中第 pos 个字符之后首次出现的位置（从 1 开始）。没找到返回 0。
int Index_KMP(SString S, SString T, int next[], int pos) {
	int i = pos; // i 指向主串 S (不回退！)
	int j = 1;   // j 指向模式串 T
	
	// [TODO] 4: 循环条件是什么？
	// 提示：i 和 j 都不能越界。注意我们下标是从 1 开始的，所以可以等于 length。
	while (i<=S.length && j<= T.length) {
		
		// [TODO] 5: 比较逻辑（和求 next 数组的逻辑惊人地相似！）
		// 提示：如果 j == 0，或者当前字符匹配成功 (S.ch[i] == T.ch[j])，携手并进 (i++, j++)。
		// 提示：如果不匹配，灵魂操作来了：主串 i 绝不回头！只有模式串 j 回退到 next[j]。
		// 你的代码写在这里...
		if ( j == 0 || S.ch[i] == T.ch[j] ) {
			i++;j++;
		} else {
			j = next[j];
		}
	}
	
	// [TODO] 6: 判断是否匹配成功
	// 提示：如果跳出循环时，j 越过了模式串的长度 (j > T.length)，说明找完了！
	// 提示：返回匹配成功的起始位置 (也就是现在的 i 减去 模式串的长度)。
	// 你的代码写在这里...
	if (j > T.length) {
		return i - T.length;
	} else {
		return 0; // 匹配失败
	}
}

// ==========================================
// 4. 终极测试模块
// ==========================================
int main() {
	SString S, T;
	// 主串
	InitString(&S, "abacabaababaa"); 
	// 模式串 (就是我们刚才手算的那道题！)
	InitString(&T, "ababaa");       
	
	int next[MAXLEN];
	int nextval[MAXLEN];
	
	// 1. 测试 next 数组
	get_next(T, next);
	printf("T 的 next 数组 (应为 0 1 1 2 3 4): \n");
	for (int i = 1; i <= T.length; i++) {
		printf("%d ", next[i]);
	}
	printf("\n\n");
	
	// 2. 测试 nextval 数组
	get_nextval(T, nextval);
	printf("T 的 nextval 数组: \n");
	for (int i = 1; i <= T.length; i++) {
		printf("%d ", nextval[i]);
	}
	printf("\n\n");
	
	// 3. 测试 KMP 匹配
	// 在 S 中寻找 T，期待在下标为 8 的位置找到完整匹配
	int index = Index_KMP(S, T, next, 1);
	printf("匹配结果 (应为 8): %d\n", index);
	
	return 0;
}
