#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {

	omp_set_num_threads(3);
    #pragma omp parallel if (omp_get_num_threads())
	{
		if (omp_get_num_threads() > 1)
		{
			printf("1st section %d of %d \n", omp_get_thread_num(), omp_get_num_threads());
		}
	}
	printf("\n");
	omp_set_num_threads(1);
    #pragma omp parallel if (omp_get_num_threads())
	{
		if (omp_get_num_threads() > 1)
		{
			printf("2nd section %d of %d \n", omp_get_thread_num(), omp_get_num_threads());
		}
	}

    return 0;
}
