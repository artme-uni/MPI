#include "Matrix.h"

Column Matrix::mult(const Column &cur) const
{
    double * col_part= new double[d.count_C[d.PR_rank]];
    MPI_Scatterv(cur.get_values(), d.count_C, d.index_C, MPI_DOUBLE, col_part, d.count_C[d.PR_rank], MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);

    double *result = new double[n];

    for (int m = 0; m < n; ++m)
    {
        result[m] = 0;
    }

    for (int l = 0; l < d.count_M[d.PR_rank]; ++l)
    {
        result[l % n] += part[l] * col_part[l / n];
    }


    double *sum = new double[n];
    MPI_Reduce(result, sum, n, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(sum, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    Column res(n);

    for (int l = 0; l < n; ++l)
    {
        res.set(l, sum[l]);
    }

    delete[] sum;
    delete[] result;

    return res;


}
