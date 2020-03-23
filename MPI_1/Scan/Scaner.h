#ifndef MPI_SCANER_H
#define MPI_SCANER_H

#include <fstream>
#include "../Matrix/Column.h"
#include "../Matrix/Matrix.h"

void matrix_scan(std::ifstream &in, Matrix& A, Column& B);

#endif //MPI_SCANER_H
