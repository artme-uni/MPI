#ifndef MPI_MATRIX_H
#define MPI_MATRIX_H

#include "Column.h"
#include "../Distribution.h"
#include <cstdlib>


class Matrix
{
private:
    double *values = nullptr;
    double *part = nullptr;

    int n;

    Distribution d;

public:
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

    void print_diagonal(std::ostream &out)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                {
                    out << 2 << " ";
                    continue;
                }
                out << 1 << " ";
            }

            out << std::endl;
        }

        out << std::endl;

        srand(999);

        for (int k = 0; k < n; ++k)
        {
            out << rand() % 100 << std::endl;
        }
    }

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

    void init_part();
};

#endif //MPI_MATRIX_H