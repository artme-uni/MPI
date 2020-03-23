#ifndef MPI_SOLE_H
#define MPI_SOLE_H

#include "Matrix/Matrix.h"
#include "Matrix/Column.h"
#include "Distribution.h"

Column sole_solution(Matrix &A, Column &B, Distribution &d);

#endif //MPI_SOLE_H
