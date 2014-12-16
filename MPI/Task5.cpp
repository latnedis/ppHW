#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[]) {
    int size, rank;
    int n = 5, m = 5, matrix[25],vector[5];
    int resultProc[5];
    int result[5];
    for (int i = 0; i < n; i++) {
        result[i] = 0;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (int i = 0; i < n*m; i++) {
            matrix[i] = i;
        }
        for (int i = 0; i < m; i++) {
            vector[i] = i;
        }
    }
    MPI_Bcast(matrix, n*m, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector, m, MPI_INTEGER, 0, MPI_COMM_WORLD);
    int k = n / size;
    int l = k * rank;
    int r = k * (rank + 1);
    if (rank == size - 1) {
        r = n;
    }
    for (int i = 0; i < n; i++) {
        resultProc[i] = 0;
    }
    for (int i = l; i < r; i++) {
        for (int j = 0; j < m; j++) {
            resultProc[i] += matrix[i * n + j] * vector[j];
        }
    }
    MPI_Reduce(&resultProc, &result, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Product matrix on vector: ";
        for (int i = 0; i < n; i++) {
            cout << result[i] << ' ';
        }
    }

    MPI_Finalize();
    return 0;
}