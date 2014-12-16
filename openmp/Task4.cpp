#include <iostream>
#include <omp.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int i, max, min, n = 10;
	int *a = new int [n];
	int *b = new int [n];

    for (i = 0; i < n; i++) {
        a[i] = i;
    }

	for (int i = 0; i < n; i++) {
		b[i] = n - i - 1;
	}

	omp_set_num_threads(2);
	#pragma omp parallel if (omp_get_num_threads()) shared(max, min, n)
	{

		if (omp_get_thread_num() == 0) {
			min = a[0];
			for (int i = 0; i < n; i++) {
				if (a[i] < min)
					min = a[i];
			}
		}
		else if (omp_get_thread_num() == 1){
			max = b[0];
			for (int i = 0; i < n; i++) {
				if (b[i] > max)
					max = b[i];
			}
		}
	}

	printf("min from a = %d, max from b = %d \n", min, max);
}
