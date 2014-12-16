#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {

	int a = 0, b = 0;
	printf("Before 1st section: a = %d, b = %d \n", a, b);
	omp_set_num_threads(2);
    #pragma omp parallel private(a) firstprivate(b)
	{
		//a = 1;
		int curThread = omp_get_thread_num();
		a += curThread;
		b += curThread;
		printf("1st section: thread = %d, a = %d, b = %d \n", curThread, a, b);
	}
	printf("After 1st section: a = %d, b = %d \n", a, b);
	printf("Before 2st section: a = %d, b = %d \n", a, b);

	omp_set_num_threads(4);
    #pragma omp parallel shared (a) private(b)
	{
		//b = 1;
		int curThread2 = omp_get_thread_num();
		a -= curThread2;
		b -= curThread2;
		printf("2st section: thread2 = %d, a = %d, b = %d \n", curThread2, a, b);
	}
    printf("After 2st section: a = %d, b = %d \n", a, b);
    return 0;
}

//Не будет работать, потому что использование private подразумевает инициализирование внутри параллельной секции.
