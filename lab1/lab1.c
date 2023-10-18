#include <stdio.h>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int array[10] = {10,9,8,7,6,5,4,3,2,1};
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j + 1 < 10; j++)
		{
			if(array[j] <= array[j + 1])
				continue;
			else
				swap(&array[j], &array[j +1]);
		}
	}

	for(int i = 0; i < 10; i++)
		printf("%d ", array[i]);

	return 0;
}
