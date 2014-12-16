//#include <iostream>
#include <mpi.h>
//#include <time.h>
using namespace std;

void main(int argc, char* argv[])
{
    int n = 10;
    int numbers[10];
    int size,rank,sum,count;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            numbers[i] = i;
        }
    }
    MPI_Bcast(numbers, n, MPI_INTEGER, 0, MPI_COMM_WORLD);

    int k = n/size;
    int left = rank*k;
    int right = k*(rank+1);
    if (rank == size - 1) {
        right = n;
    }
    int localsum = 0;
    int digitcount = 0;
    for(int i = left+1; i < right; i++){
        if (numbers[i] > 0) {
            localsum += numbers[i];
            digitcount++;
        }
    }
    MPI_Reduce(&localsum,&sum,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&digitcount,&count,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank == 0){
        printf("Arifmetic average=%f\n", (double)sum/count);
    }
    MPI_Finalize();
    return(0);
}