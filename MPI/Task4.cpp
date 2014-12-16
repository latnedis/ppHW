#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
    int x[10], y[10];
    int s_p, p_s_p = 0;
    MPI_Status status;
    int rank, size;
    int n = 10;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0) {
        for (int i = 0; i < n; i++) {
            x[i] = i;
        }
        for (int i = 0; i < n; i++) {
            y[i] = i;
        }
    }
    MPI_Bcast(x, n, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(y, n, MPI_INTEGER, 0, MPI_COMM_WORLD);
    int k = n/size;
    int left = rank*k;
    int right = k*(rank+1);
    if (rank == size - 1) {
        right = n;
    }

    for(int i = left; i < right; i++){
        p_s_p = p_s_p + x[i] * y[i];
    }
    MPI_Reduce(&p_s_p,&s_p,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
    if (rank == 0)  {
        cout << endl << "Scalar product: " << s_p;
    }
    MPI_Finalize();
    return 0;
}