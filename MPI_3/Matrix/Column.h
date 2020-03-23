#ifndef MPI_COLUMN_H
#define MPI_COLUMN_H

#include <cmath>
#include <iostream>
#include <mpi.h>
#include "../Distribution.h"

class Column
{
private:
    double *values = nullptr;

    int n;


public:
    explicit Column(int n) : n(n)
    {
        values = new double[n];
    }

    void init_all()
    {
        MPI_Bcast(values, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    double get(int i) const
    {
        return values[i];
    }

    double *get_values() const
    {
        return values;
    }


    void set(int i, double val)
    {
        values[i] = val;
    }

    void set_zero(Distribution &d)
    {
        for (int i = 0; i < n; ++i)
        {
            set(i, 0);
        }
    }


    int get_size() const
    {
        return n;
    }

    void print(std::ostream &out)
    {
        for (int i = 0; i < n; ++i)
        {
            out << get(i) << " " << std::endl;
        }
    }

    double dot_product(Column &other)
    {
        double sum = 0;

        for (int i = 0; i < n; ++i)
        {
            sum += this->get(i) * other.get(i);
        }

        return sum;
    }

    Column mult_by_number(double cur)
    {
        Column res(n);

        for (int i = 0; i < n; ++i)
        {
            res.set(i, get(i) * cur);
        }

        return res;
    }

    double module()
    {
        double sum = 0;

        for (int i = 0; i < n; ++i)
        {
            sum += get(i) * get(i);
        }

        return sqrt(sum);
    }

    Column(const Column &x)
    {
        n = x.n;
        values = new double[n];
        *values = *x.values;
    }

    Column(Column &&x)
    {
        values = x.values;
        n = x.n;
        x.values = nullptr;
    }

    Column &operator=(const Column &x)
    {
        n = x.n;

        if (&x == this)
            return *this;

        delete values;
        values = new double[n];

        *values = *x.values;

        return *this;
    }

    Column &operator=(Column &&x)
    {
        this->n = x.n;

        if (&x == this)
            return *this;

        delete values;
        values = new double[n];

        values = x.values;
        x.values = nullptr;

        return *this;
    }

    Column operator+(const Column &right) const
    {
        Column res(n);
        for (int i = 0; i < n; ++i)
        {
            res.set(i, get(i) + right.get(i));
        }

        return res;
    }

    Column operator-(const Column &right) const
    {
        Column res(n);
        for (int i = 0; i < n; ++i)
        {
            res.set(i, get(i) - right.get(i));
        }

        return res;
    }
};


#endif //MPI_COLUMN_H
