#ifndef MPI_SCANER_H
#define MPI_SCANER_H

#include <fstream>
#include "../Matrix/Column.h"
#include "../Matrix/Matrix.h"

void init_values(std::ifstream &in, Matrix& A, Column& B);

#endif //MPI_SCANER_H
