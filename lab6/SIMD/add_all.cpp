#include <nmmintrin.h>
#include <stdio.h>

int  main()
{
	__m128 v0 = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
	__m128 v1 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(2, 3, 0, 1));

	v0 = _mm_add_ps(v0, v1);
	
	v1 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(0, 1, 2, 3));

	v0 = _mm_add_ps(v0, v1);

//	float a[4];
//	_mm_storeu_ps(a, v0);

	float x = _mm_cvtss_f32(v0);
	
	printf("x = %lf\n", x);

//	printf("a[0] = %lf, a[1] = %lf, a[2] = %lf, a[3] = %lf\n", a[0], a[1], a[2], a[3]);
}

