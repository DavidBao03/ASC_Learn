#include <immintrin.h>
#include <stdio.h>

float a[4] = {1, 2, 3, 4};
float b[4] = {5, 6, 7, 8};
float c[4] = {9, 10, 11, 12};
float d[4] = {13, 14, 15, 16};

void print_vec(float* vec)
{
	for(int i = 0; i < 4; i++)
		printf("%2lf ", vec[i]);
	printf("\n");
}

int  main()
{
	
	__m128 va = _mm_loadu_ps(a);
	__m128 vb = _mm_loadu_ps(b);
	__m128 vc = _mm_loadu_ps(c);
	__m128 vd = _mm_loadu_ps(d);

	




}
