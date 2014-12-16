#include <mpi.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {

    MPI_Status status;
    int rank,size;
    int height = 10;
    int n =100;
    int a[100];
    for(int i = 0; i < n; i++)
        a[i] = i;

    int min = a[20];
    int bufsize;
    int *buf;
    bufsize = 3 * MPI_BSEND_OVERHEAD + min;
    buf = (int *)malloc(bufsize);
    //Иницилизируем mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //Отправляем другим процессам
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Buffer_attach(buf, bufsize);
    double startSend, endSend, startSsend, endSsend, startBsend, endBsend, startRsend, endRsend;
    if(rank == 0){
        //SEND
        startSend = MPI_Wtime();
        MPI_Send(&min,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Recv(&min,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        endSend = MPI_Wtime();

        //SSEND
        startSsend = MPI_Wtime();
        MPI_Ssend(&min,1,MPI_INT,1,1,MPI_COMM_WORLD);
        MPI_Recv(&min,1,MPI_INT,1,1,MPI_COMM_WORLD,&status);
        endSsend = MPI_Wtime();

        //BSEND
        startBsend = MPI_Wtime();
        MPI_Bsend(&min,1,MPI_INT,1,2,MPI_COMM_WORLD);
        MPI_Recv(&min,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
        endBsend = MPI_Wtime();

        //RSEND-
        startRsend = MPI_Wtime();
        MPI_Rsend(&min,1,MPI_INT,1,3,MPI_COMM_WORLD);
        MPI_Recv(&min,1,MPI_INT,1,3,MPI_COMM_WORLD,&status);
        endRsend = MPI_Wtime();
//Вывод времени
        cout<<"Send = "<<endSend-startSend<<" Ssend = "<<endSsend-startSsend<<" Bsend = "<<endBsend-startBsend<<" Rsend = "<<endRsend-startRsend<<endl;

    }

    if(rank == 1){

        //SEND
        MPI_Recv(&min,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Send(&min,1,MPI_INT,0,0,MPI_COMM_WORLD);

        //SSEND
        MPI_Recv(&min,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        MPI_Ssend(&min,1,MPI_INT,0,1,MPI_COMM_WORLD);

        //BSEND
        MPI_Recv(&min,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
        MPI_Bsend(&min,1,MPI_INT,0,2,MPI_COMM_WORLD);

        //RSEND
        MPI_Recv(&min,1,MPI_INT,0,3,MPI_COMM_WORLD,&status);
        MPI_Rsend(&min,1,MPI_INT,0,3,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}