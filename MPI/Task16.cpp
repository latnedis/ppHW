#include <iostream>
#include <mpi.h>
using namespace std;
//подынтегральная функция
float f(float x) {
return 4/ (1+x*x);
}
int main(int argc, char** argv)
{
    float a, b, len, ar, br, x0, x1, h, s, r;
    int size, rank; //число процессов, номер текущего процесса
    const int n = 100; //число точек разбиения каждого интеграла
    //пределы интегрирования
    a = 0.0f;
    b = 1.0f;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    len = (b - a) / size; //определяем длину отрезка [aj,bj]
    ar = a + rank*len; //для текущего процесса определяем отрезок [aj,bj]
    br = ar + len;
    x0=x1 = ar;
    h = (br - ar) / n;
    //вычисляем интеграл по отрезку [aj,bj]
    s = 0.0f;
    while (x1<br) {
        x1 = x0 + h;
        s = s + f((x1 + x0) / 2)*h;
        x0 = x1;
    }
    //в переменную r записываем просуммированный результат
    MPI_Reduce(&s, &r, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("integral=%f\n", r);
    MPI_Finalize();
    return 0;
}