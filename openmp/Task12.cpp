#include <iostream>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {

	int i, max, array[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
        array[i] = rand() %100;
    }

	max = 0;

	omp_set_num_threads(8);
	#pragma omp parallel for private(i) shared(max)
	for(i = 0; i < 10; i++){

			#pragma omp critical
			{
				if(array[i] % 7 == 0 && array[i] > max)
					max = array[i];
			}
	}

	printf("Max / 7= %d", max);
}
