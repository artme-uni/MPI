#include "Matrix.h"
#include <mpi.h>

Column Matrix::mult(const Column &cur) const
{

    Column result(size);
    double temp = 0;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            temp += this->get(i, j) * cur.get(j);
        }

        result.set(i, temp);
        temp = 0;
    }

    return result;
}