#ifndef MPI_MATRIX_H
#define MPI_MATRIX_H

#include "Column.h"
#include <cstdlib>

class Matrix
{
private:
    double *values = nullptr;
    double *part = nullptr;

    int n;

public:
    Distribution d;

    explicit Matrix(int n, Distribution &d) : n(n), d(d)
    {
        if (d.PR_rank == 0)
            values = new double[n * n];
    }

    double get(int i, int j) const
    {
        return values[i + n * j];
    }

    double *get_values()
    {
        return values;
    }

    double *get_part()
    {
        return part;
    }

    void set(int i, int j, double val)
    {
        values[i + n * j] = val;
    }

    Column mult(const Column &out) const;


    void print(std::ostream &out)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                out << get(i, j) << " ";
            }

            out << std::endl;
        }

        out << std::endl;
    }

    void transposition() const
    {
        if(values == nullptr)
            return;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(i == j)
                    continue;

                double temp = values[j + n*i];
                values[j + n*i] = values[i + n*j];
                values[i + n*j] = temp;
            }
        }
    }

    void init_part()
    {
        transposition();

        part = new double[d.count_M[d.PR_rank]];

        MPI_Scatterv(values, d.count_M, d.index_M, MPI_DOUBLE, part, d.count_M[d.PR_rank], MPI_DOUBLE, 0,
                     MPI_COMM_WORLD);

        transposition();

    }
};

#endif //MPI_MATRIX_H