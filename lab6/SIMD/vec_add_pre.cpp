#include <stdio.h>

int main()
{
	float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	float b[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	
	float c[4];
	
	for(int i = 0; i < 4; i++)
		c[i] = a[i] + b[i];
	
	printf("c[0] = %lf, c[1] = %lf, c[2] = %lf, c[3] = %lf\n", c[0], c[1], c[2], c[3]);
}
