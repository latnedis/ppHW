#include <iostream>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
    int size, rank, procMax, max;
    MPI_Status status;
    int n = 10;
    int numbers[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        srand(time(0));
        for (int i = 0; i < n; i++) {
            numbers[i] = i;
        }
    }

    MPI_Bcast(numbers, n, MPI_INTEGER, 0, MPI_COMM_WORLD);
    int k = n / size;
    int l = k * rank;
    int r = k * (rank + 1);
    if (rank == size - 1) {
        r = n;
    }
    procMax = numbers[l];
    for (int i = l + 1; i < r; i++) {
        if (procMax < numbers[i]) {
            procMax = numbers[i];
        }
    }

    if (rank == 0) {
        max = procMax;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&procMax, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (max < procMax) {
                max = procMax;
            }
        }
        cout << endl << "Max: " << max;
    }
    else {
        MPI_Send(&procMax, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
