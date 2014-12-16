#include <iostream>
#include <mpi.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 11;
    int *a = new int[100];
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    int myRank, size;

    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myRank != size-1) {
        for (int i = myRank; i < n/2; i+=(size-1)) {
            swap(a[i], a[n-1-i]);
        }
        MPI_Send(a, n, MPI_INT, size-1, 0, MPI_COMM_WORLD);
    } else {
        cout << "Array:" << endl;
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < size-1; i++) {
            int *tempArr = new int[n];
            MPI_Recv(tempArr, n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            for (int j = i; j < n/2; j+=(size-1)) {
                a[j] = tempArr[j];
                a[n-1-j] = tempArr[n-1-j];
            }
        }
        cout << "Return array :" << endl;
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    MPI_Finalize();
    return 0;
}