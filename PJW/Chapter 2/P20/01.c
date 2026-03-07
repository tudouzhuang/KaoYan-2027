#include <stdio.h>

void PrintLine(int *line, int length)
{
	printf("数组: ");
	for(int i = 0; i < length; i++)
	{
		printf("%d ", line[i]);
	}
	return;
}

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
	
	return min_value;
}

int main()
{
	//这里的顺序表直接用数组表示
	int num[] = {2,5,12,34,42,12,52,231,1,4,6,9};
	int len = 12;
	PrintLine(num,12);
	DeleteMin(num,12);
	PrintLine(num,11);
	return 0;
}
