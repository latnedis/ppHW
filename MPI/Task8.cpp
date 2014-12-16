#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]){
    int rank, size;
    int digit = 2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0) {
        MPI_Ssend(&digit,1,MPI_INTEGER,1,3,MPI_COMM_WORLD);
    } else {
        MPI_Recv(&digit,1,MPI_INTEGER,rank-1,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        digit++;
        if(rank != size-1) {
            MPI_Ssend(&digit,1,MPI_INTEGER,rank+1,4,MPI_COMM_WORLD);
        } else {
            MPI_Ssend(&digit,1,MPI_INTEGER,0,5,MPI_COMM_WORLD);
        }

    }
    if(rank == 0) {
        MPI_Recv(&digit,1,MPI_INTEGER,size-1,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        cout << "Digit is " << digit;
    }
    MPI_Finalize();
    return 0;
}