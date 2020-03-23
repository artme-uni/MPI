#include "Sole.h"

Column sole_solution(Matrix &A, Column &B, Distribution &d)
{
    Column X(B.get_size());
    X.set_zero(d);
    double precision = 0.001;
    double diff = 0;

    int count = 0;

    do
    {
        ++count;

        Column Y = A.mult(X) - B;
        Column AY = A.mult(Y);

        double t;
        if (AY.dot_product(AY) == 0)
        {
            t = 0;
        } else
        {
            t = Y.dot_product(AY) / AY.dot_product(AY);
        }

        diff = Y.module() / B.module();
        X = (X - Y.mult_by_number(t));

    } while (diff >= precision);

    std::cout << "Iteration count = " << count << std::endl;

    return X;
}