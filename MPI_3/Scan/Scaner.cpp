#include "Scaner.h"

void init_values(std::ifstream &in, Matrix& A, Column& B)
{
    int size = B.get_size();

    char buffer[10];

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            in.getline(buffer, 10, ' ');
            A.set(i, j, atof(buffer));
        }

        in.getline(buffer, 10, '\n');
        A.set(i, size - 1, atof(buffer));
    }

    in.getline(buffer, 10);

    for (int k = 0; k < size; ++k)
    {
        in.getline(buffer, 10, '\n');
        B.set(k, atof(buffer));
    }
}