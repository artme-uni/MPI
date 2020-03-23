
#include <iostream>
#include <stdlib.h>
#include <vector>

#include<mpi.h>

#include "Sole.h"
#include "Scan/Scaner.h"

int main(int argc, char **argv)
{
    double t1 = MPI_Wtime();


    int PR_count, PR_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &PR_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &PR_rank);


    std::ifstream in("/Users/twiggy/Doc_Git/Concurrent/MPI/MPI_3/cmake-build-debug/input.txt");
    std::ofstream out("/Users/twiggy/Doc_Git/Concurrent/MPI/MPI_3/cmake-build-debug/output.txt");
    if (!in.is_open())
    {
        std::cerr << "File cannot be open\n";
        exit(-1);
    }

    int size = 1500;
    Distribution dist(PR_count, PR_rank, size);
    Matrix A(size, dist);
    Column B(size);

    if (PR_rank == 0)
    {
        init_values(in, A, B);
    }

    A.init_part();
    B.init_all();

    Column C = sole_solution(A, B, dist);

    if (PR_rank == 0)
    {
       C.print(out);
    }

    in.close();
    out.close();


    double t2 = MPI_Wtime();
    std::cout << PR_rank << " : " << t2 - t1 << std::endl;


    MPI_Finalize();
    return 0;
}