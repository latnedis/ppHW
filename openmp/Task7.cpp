#include <iostream>
#include <omp.h>
#include <stdlib.h>

int main() {

	int i;
	int a[12], b[12], c[12];

	omp_set_num_threads(3);
	#pragma omp parallel for private(i) schedule(static, 3)
	for (i = 0; i < 12; i++) {
		a[i] = i;
		b[i] = 2 * i - 1;
		printf("Thread %d of %d, a[%d] = %d, b[%d] = %d \n", omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
	}
	printf("Also... \n");
	omp_set_num_threads(4);
	#pragma omp parallel for private(i) schedule(dynamic, 2)
	for (i = 0; i < 12; i++) {
		c[i] = a[i] + b[i];
		printf("Thread %d of %d, a[%d] = %d, b[%d] = %d, c[%d] = %d \n", omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i], i, c[i]);
	}
}
