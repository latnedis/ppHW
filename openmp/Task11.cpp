#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {

	int i, count = 0, a[30];

	for (int i = 0; i < 30; i++) {
        a[i] = rand();
    }

	omp_set_num_threads(8);
	#pragma omp parallel for private(i)
	for (i = 0; i < 30; i++) {
		if(a[i] % 9 == 0){
			#pragma omp atomic
				count++;
		}
	}

	printf("Count of / 3 = %d \n", count);
}
