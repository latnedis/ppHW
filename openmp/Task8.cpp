#include <iostream>
#include <omp.h>
#include <stdlib.h>

int main() {

	int i;
	double a[16000], b[16000];

	#pragma omp parallel for
	for (i = 0; i < 16000; i++) {
		a[i] = i;
	}

	printf("\n Static:... \n");
	omp_set_num_threads(8);
	#pragma omp parallel for private(i) schedule(static, 2)
	for (i = 0; i < 16000; i++) {
		if (i == 0 || i == 16000)
			b[i] = i;
		else
			b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
		printf("Thread = %d, b[%d] = %f \n", omp_get_thread_num(), i, b[i]);
	}

	printf("\n Dynamic:... \n");
	omp_set_num_threads(8);
	#pragma omp parallel for private(i) schedule(dynamic, 2)
	for (i = 0; i < 16000; i++) {
		if (i == 0 || i == 16000)
			b[i] = i;
		else
			b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
		printf("Thread = %d, b[%d] = %f \n", omp_get_thread_num(), i, b[i]);
	}

	printf("\n Guided:... \n");
	omp_set_num_threads(8);
	#pragma omp parallel for private(i) schedule(guided, 2)
	for (i = 0; i < 16000; i++) {
		if (i == 0 || i == 16000)
			b[i] = i;
		else
			b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
		printf("Thread = %d, b[%d] = %f \n", omp_get_thread_num(), i, b[i]);
	}

	printf("\n Runtime:... \n");
	omp_set_num_threads(8);
	#pragma omp parallel for private(i) schedule(runtime)
	for (i = 0; i < 16000; i++) {
		if (i == 0 || i == 16000)
			b[i] = i;
		else
			b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
		printf("Thread = %d, b[%d] = %f \n", omp_get_thread_num(), i, b[i]);
	}
}
