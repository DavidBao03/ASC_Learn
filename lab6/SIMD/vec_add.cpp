#include <immintrin.h>
#include <stdio.h>

float a[4] = {1, 3, 5, 7};
float b[4] = {2, 4, 6, 8};
float c[4];

int  main()
{
	
	__m128 va = _mm_loadu_ps(a);
	__m128 vb = _mm_loadu_ps(b);
	__m128 vc = _mm_loadu_ps(c);

	vc = _mm_add_ps(va, vb);
	
	_mm_storeu_ps(c, vc);

	
	printf("c[0] = %lf, c[1] = %lf, c[2] = %lf, c[3] = %lf\n", c[0], c[1], c[2], c[3]);
}
