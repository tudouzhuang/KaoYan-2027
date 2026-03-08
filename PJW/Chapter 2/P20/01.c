#include <stdio.h>
// 输出数组的函数
void PrintLine(int *line, int length)
{
	printf("数组: ");
	for(int i = 0; i < length; i++)
	{
		printf("%d ", line[i]);
	}
	printf("\n");
	return;
}

// 01.第一题的方法
int DeleteMin(int *line, int length)
{
	if(line == NULL || length <= 0)
		return -1;
	
	int min_index = 0;
	
	for(int i = 1; i < length; i++)
	{
		if(line[i] < line[min_index])
		{
			min_index = i;
		}
	}
	
	int min_value = line[min_index];
	
	line[min_index] = line[length - 1];
	
	return length - 1;
}

// 02.倒置数组，第一个和最后一个交换，一直换到一半长度
void ReverseSort(int *line,int length)
{
	int temp;
	for(int i=0;i<length/2;i++){
		temp = line[i];
		line[i] = line[length-i-1];
		line[length-i-1] = temp;
	}
	return ;
}

// 03.删除所有值为x的数据元素
int DeleteX(int *line,int length,int x)
{
	int movement = 0;
	for(int i=0;i<length;i++){
		// 如果找到值x,先置零,然后之后的元素都要向前移动movement的长度
		if(line[i] == x)
		{
			movement ++;
			continue;
		}
		line[i-movement] = line[i];
	}
	return length - movement;
}

// 10.循环左移算法
void LeftRotate(int *line,int length,int p)
{
	p = p % length; //先保证不超过length
	int temp[p];
	for(int i=0;i<length;i++)
	{
		if(i < p)
			temp[i] = line[i];
		else if(i >= p && i < length - p){
			line[i-p] = line[i];
		}
		else{
			line[i-p] = line[i];
			line[i] = temp[i + p - length];
		}
		
	}
}
int main()
{
	//这里的顺序表直接用数组表示
	int num[] = {2,5,12,34,42,5,5,5,12,52,231,1,4,6,9};
	int len = 15;
	// 01
	PrintLine(num,len);
	len = DeleteMin(num,len);
	PrintLine(num,len);
	// 02
	ReverseSort(num,len);
	PrintLine(num,len);
	// 03
	len = DeleteX(num,len,5);
	PrintLine(num,len);
	// 10
	LeftRotate(num,len,3);
	PrintLine(num,len);
	return 0;
}
