#include "Matrix.h"

void Matrix::init_part()
{
    part = new double[d.count_M[d.PR_rank]];

    MPI_Scatterv(values, d.count_M, d.index_M, MPI_DOUBLE, part, d.count_M[d.PR_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

Column Matrix::mult(const Column &cur) const
{
    double *res_part = new double[d.count_M[d.PR_rank]];

    for (int i = 0; i < d.count_C[d.PR_rank]; i++)
    {
        res_part[i] = 0;

        for (int j = 0; j < n; j++)
        {
            res_part[i] += part[j + i * n] * cur.get_ptr()[j];
        }
    }

    double *res_row = new double[n];

    MPI_Allgatherv(res_part, d.count_C[d.PR_rank], MPI_DOUBLE, res_row, d.count_C, d.index_C, MPI_DOUBLE, MPI_COMM_WORLD);

    Column result(n);
    for (int l = 0; l < n; ++l)
    {
        result.set(l, res_row[l]);
    }

    delete[] res_part;
    delete[] res_row;

    return result;
}