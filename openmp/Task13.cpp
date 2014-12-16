#include <omp.h>
#include <stdio.h>

int main(){

	int i = 0;

	omp_set_num_threads(8);
	int threads = omp_get_num_threads();
	#pragma omp parallel if(omp_get_thread_num())
	if (omp_get_thread_num() == i){
		printf("Thread = %d \n", omp_get_thread_num());
		i++;
	}

	return 0;
}
