#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {

	int d[6][8];
	double average = 0;
	int count = 0;

	for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = rand();
        }
    }

	int min = d[0][0], max = d[0][0];

	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						average += d[i][j];
					}
				}
				average = average / (6 * 8);
				printf("Average = %f \n", average);
			}

			#pragma omp section
			{
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] < min)
							min = d[i][j];
						if (d[i][j] > max)
							max = d[i][j];
					}
				}
				printf("Max = %d, Min = %d \n", max, min);
			}

			#pragma omp section
			{
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] % 3 == 0)
							count++;
					}
				}
				printf("Count of / 3 = %d \n", count);
			}
		}
	}


}
