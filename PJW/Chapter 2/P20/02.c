#include <stdio.h>

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

int main()
{
	//这里的顺序表直接用数组表示
	int num[] = {2,5,12,34,42,12,52,231,1,4,6,9};
	int len = 12;
	PrintLine(num,12);
	ReverseSort(num,12);
	PrintLine(num,12);
	return 0;
}
