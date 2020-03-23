#ifndef MPI_MATRIX_H
#define MPI_MATRIX_H

#include "Column.h"

class Matrix
{
private:
    double *values;
    int size;
    int PR_count;
    int PR_rank;

    void Create()
    {
        values = new double[size*size];
    }

public:
    explicit Matrix(int n, int count, int rank) : size(n), PR_count(count), PR_rank(rank)
    {
        Create();
    }

    double get(int i, int j) const
    {
        return values[i + size*j];
    }

    double* get_ptr() const
    {
        return values;
    }

    void set(int i, int j, double val)
    {
        values[i + size*j] = val;
    }

    Column mult(const Column &cur) const;

    void print(std::ostream &out)
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                out << get(i, j) << " ";
            }

            out << std::endl;
        }

        out << std::endl;
    }
};

#endif //MPI_MATRIX_H