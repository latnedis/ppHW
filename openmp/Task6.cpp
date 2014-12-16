#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main(){

	int a[10], b[10], j;
	double average = 0, average2 = 0;

	for (int i = 0; i < 10; i++) {
		a[i] = i + 1;
	}
	for (int i = 0; i < 10; i++) {
		b[i] = 10;
	}

	#pragma omp parallel for private(j) reduction(+:average)
	for(j = 0; j < 10; j++) {
			average += a[j];
	}

	#pragma omp parallel for private(j) reduction(+:average2)
	for(j = 0; j < 10; j++) {
			average2 += b[j];
	}

	average = average / 10;
	average2 = average2 / 10;

	if (average > average2)
		printf("Average of first array is more than average of second array \n");
	else if(average < average2)
		printf("Average of second array is more than average of first array \n");
	else
		printf("Average of first and second arrays are similar \n");

}
