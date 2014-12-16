#include <iostream>
#include <omp.h>
#include <stdlib.h>

int main() {

	int i, j;
	int d[6][8];

	for (i = 0; i < 6; i++) {
		for(j = 0; j < 8; j++) {
			d[i][j] = rand();
		}
	}

	int max = d[0][0], min = d[0][0];

	omp_set_num_threads(8);
	#pragma omp parallel for private(i, j) shared(max, min)
	for(i = 0; i < 6; i++){
		for(j = 0; j < 8; j++) {

			#pragma omp critical
			{
				if(d[i][j] > max)
					max = d[i][j];
			}
			#pragma omp critical
			{
				if(d[i][j] < min)
					min = d[i][j];
			}
		}
	}
	printf("max = %d, min = %d \n", max, min);

}
