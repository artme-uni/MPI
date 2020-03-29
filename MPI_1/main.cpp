#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "Sole.h"
#include "Scan/Scaner.h"

int main(int argc, char **argv)
{

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in.is_open())
    {
        std::cerr << "File cannot be open\n";
        exit(-1);
    }

    int size = 1500;

    Matrix A(size, 0, 0);
    Column B(size);

    matrix_scan(in, A, B);

    clock_t start = clock();
    Column C = sole_solution(A, B);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);

    C.print(out);


    return 0;
}