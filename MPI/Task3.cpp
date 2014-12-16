#include <iostream>
#include <mpi.h>
#include <time.h>
using namespace std;
int main(int argc, char* argv[]){
    int rank, size,result;
    int raw = 4;
    int col = 4;
    int length = raw*col;
    int x[16];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0) {
        for(int i = 0; i < length; i++) {
            x[i] = i;
        }
    }
    MPI_Bcast(x, length, MPI_INTEGER, 0, MPI_COMM_WORLD);
    int raws_in_process = raw/size;
    int first_raw  = raws_in_process * rank;
    int last_raw = raws_in_process * (rank+1);
    if(rank == size - 1) {
        last_raw = raw;
    }
    int max_in_process = -1;
    int min_in_row = x[first_raw*col];
    for(int i = first_raw*col + 1; i < last_raw*col; i++) {
        if(x[i] < min_in_row) {
            min_in_row = x[i];
        }
        if(i != 0 && (i + 1) % col == 0) {
            if(min_in_row > max_in_process) {
                max_in_process = min_in_row;
            }
            if(i + 1 != length) {
                min_in_row = x[(first_raw + 1)*col];
            }
        }
    }
    MPI_Reduce(&max_in_process,&result,1,MPI_INTEGER,MPI_MAX,0,MPI_COMM_WORLD);
    if(rank == 0) {
        cout << endl;
        cout << "MaxMin = " << result;
    }
    MPI_Finalize();
    return 0;
}