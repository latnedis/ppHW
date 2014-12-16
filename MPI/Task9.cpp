#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int task, rank, src, size, count, sim(1), cur;
    int n(4), i, j;
    float **a = new float *[n];
    float *buf = new float[n];
    for (i = 0; i < n; i++) {
        a[i] = new float[n];
    }
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &task);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    src = 0;
    if (rank == 0) {
        if (task == 1) {
            size = n / task;
        } else {
            size = n / (task - 1) + 1;
        }
        count = size; //количество пересылаемых данных
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                a[i][j] = i+j;
            }
        }
        printf("A: \n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%f ", a[i][j]);
            }
            printf("\n");
        }
        for (i = 1; i < task; i++) {
            if (i * size > n) { //если последним процессам остается мало данных, то уменьшаем размер передаваемых данных
                count = n - (i - 1) * size;
                if (count < 0) {
                    count = 0;
                }
            }
            MPI_Send(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            for (j = 0; j < count; j++) {
                MPI_Send(&a[(i - 1) * (size) + j][0], n, MPI_FLOAT, i, j + 1, MPI_COMM_WORLD);
                for(int k = 0; k < n; k++){
                    buf[k] = a[k][(i - 1) * (size) + j];
                }
                MPI_Send(&buf[0], n, MPI_FLOAT, i, 2*j + 1, MPI_COMM_WORLD);
            }
            MPI_Recv(&cur, 1, MPI_INT, i, n + 1, MPI_COMM_WORLD, &status);
            if(cur != 1){
                sim = 0;
            }
        }
        if(sim == 1){
            printf("Matrix is simmetric \n");
        } else {
            printf("Matrix is not simmetric \n");
        }

    } else {
        int num;
        MPI_Recv(&num, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
        float **inmsg1 = new float *[num];
        float **inmsg2 = new float *[num];
        for (j = 0; j < num; j++) {
            inmsg1[j] = new float[n];
            inmsg2[j] = new float[n];
            MPI_Recv(&inmsg1[j][0], n, MPI_FLOAT, src, j + 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&inmsg2[j][0], n, MPI_FLOAT, src, 2*j + 1, MPI_COMM_WORLD, &status);
        }
        int flag = 1;//true
        for (i = 0; i < num; i++) {
            for (j = 0; j < n; j++) {
                if(inmsg1[i][j] != inmsg2[i][j]){
                    flag = 0;//false
                }
            }
        }
        MPI_Send(&flag, 1, MPI_INT, src, n + 1, MPI_COMM_WORLD);
        for (i = 0; i < num; i++) {
            delete[]inmsg1[i];
            delete[]inmsg2[i];
        }
        delete[]inmsg1;
        delete[]inmsg2;
    }
    MPI_Finalize();
    for (i = 0; i < n; i++) {
        delete[]a[i];
    }
    delete[]a;
    return 0;
}