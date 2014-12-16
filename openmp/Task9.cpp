#include <iostream>
#include <omp.h>
#include <stdlib.h>

int main() {

	int i, j;
	int matrix[10][10], vector[10], result[10];

	for (i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
			matrix[i][j] = i + j;
		}
	}
	for (i = 0; i < 10; i++) {
		vector[i] = i;
	}

	double startTime = omp_get_wtime();

	for (i = 0; i < 10; i++) {
		result[i] = 0;
		for (j = 0; j < 10; j++)
			result[i] += matrix[i][j] * vector[j];
	}

	double endTime = omp_get_wtime() - startTime;
	printf("Consequentially time = %f \n", endTime);
	for(i = 0; i < 10; i++) {
		printf("result[%d] = %d \n", i, result[i]);
	}
	printf("\n");
	double startTime2 = omp_get_wtime();
	#pragma omp parallel for private(i, j)
	for (i = 0; i < 10; i++) {
		result[i] = 0;
		for (j = 0; j < 10; j++)
			result[i] += matrix[i][j] * vector[j];
	}
	double endTime2 = omp_get_wtime() - startTime2;
	printf("Parallel time = %f \n", endTime2);
	for(i = 0; i < 10; i++) {
		printf("result[%d] = %d \n", i, result[i]);
	}
}
