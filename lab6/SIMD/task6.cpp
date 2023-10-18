#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <immintrin.h>

struct matrix {
	double* data;
	int rows;
	int cols;
};

struct matrix* matrix_create(int rows, int cols) {
	struct matrix* m = (struct matrix *)malloc(sizeof(struct matrix));
	m -> rows = rows;
	m -> cols = cols;
	m -> data = (double *)malloc(sizeof(double) * rows * cols);
	return m;
}

void matrix_destroy(struct matrix* m) {
	free(m -> data);
	free(m);
}

void matrix_random_init(struct matrix* m) {
	for (int i = 0; i < m -> rows * m -> cols; i++) {
		m -> data[i] = (double)rand() / RAND_MAX;
	}
}

void random_init() {
	srand(time(NULL));
}

int check(struct matrix* a, struct matrix* b) {
	if (a -> rows != b -> rows || a -> cols != b -> cols) {
		return 0;
	}
	for (int i = 0; i < a -> rows * a -> cols; i++) {
		if (a -> data[i] != b -> data[i]) {
			return 0;
		}
	}
	return 1;
}

struct matrix* matrix_multiple(struct matrix* a, struct matrix* b) {
	struct matrix* c = matrix_create(a -> rows, b -> cols);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	for (int i = 0; i < a -> rows; i++) {
		for (int j = 0; j < b -> cols; j++) {
		double sum = 0;
		for (int k = 0; k < a -> cols; k++) {
			sum += a -> data[i * a -> cols + k] * b -> data[k * b -> cols + j];
		}
		c -> data[i * c -> cols + j] = sum;
		}
	}

	gettimeofday(&end, NULL);
	printf("before optimize: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
	return c;
}

struct matrix* matrix_multiple_optimize(struct matrix* a, struct matrix* b) {
	struct matrix* c = matrix_create(a -> rows, b -> cols);
	struct timeval start, end;
	gettimeofday(&start, NULL);
// 修改这段代码，使之并行化 -------------------
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < a -> rows; i++) {
		for (int k = 0; k < a -> cols; k++) {
		int j = 0;
		
		__m256d va = _mm256_set1_pd(a->data[i * (a->cols) + k]);
		for (; j < b -> cols; j += 4) {
				__m256d vb = _mm256_loadu_pd(&b -> data[k * (b -> cols) + j]);
				vb = _mm256_mul_pd(va, vb);
			
				__m256d vc = _mm256_loadu_pd(&c -> data[i * (c ->cols) + j]);
				vc = _mm256_add_pd(vc, vb);
			
				_mm256_storeu_pd(&c->data[i * (c -> cols) + j], vc);	
			}
		}
	}
// --------------------------------------------
	gettimeofday(&end, NULL);
	printf("after optimize: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
	return c;
}

int main() {
	random_init();
	struct matrix* m = matrix_create(1000, 2000);
	matrix_random_init(m);
	struct matrix* n = matrix_create(2000, 3000);
	matrix_random_init(n);
	struct matrix* r = matrix_multiple(m, n);
	struct matrix* r_optimize = matrix_multiple_optimize(m, n);
	if (check(r, r_optimize)) {
		printf("check ok\n");
	} else {
		printf("check failed\n");
	}
	
	matrix_destroy(m);
	matrix_destroy(n);
	
	matrix_destroy(r);
	matrix_destroy(r_optimize);
	return 0;
}
