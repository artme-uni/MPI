#ifndef MPI_COLUMN_H
#define MPI_COLUMN_H

#include <cmath>
#include <iostream>
#include <mpi.h>

class Column
{
private:
    double *values;
    int size;

    void Create()
    {
        values = new double[size];
    }

public:
    explicit Column(int n) : size(n)
    {
        Create();
    }

    void init_all()
    {
        MPI_Bcast(values, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    double get(int i) const
    {
        return values[i];
    }

    double* get_ptr() const
    {
        return values;
    }

    void set(int i, double val)
    {
        values[i] = val;
    }

    void set_zero()
    {
        for (int i = 0; i < size; ++i)
        {
            set(i, 0);
        }
    }

    int get_size() const
    {
        return size;
    }

    void print(std::ostream& out)
    {
        for (int i = 0; i < size; ++i)
        {
            out << get(i) << " " << std::endl;
        }
    }

    double dot_product(Column &other)
    {
        double sum = 0;

        for (int i = 0; i < size; ++i)
        {
            sum += this->get(i) * other.get(i);
        }

        return sum;
    }

    Column mult_by_number(double cur) const
    {
        Column res(size);

        for (int i = 0; i < size; ++i)
        {
            res.set(i, get(i) * cur);
        }

        return res;
    }

    double module()
    {
        double sum = 0;

        for (int i = 0; i < size; ++i)
        {
            sum += get(i)*get(i);
        }

        return sqrt(sum);
    }

    Column(const Column &x)
    {
        size = x.size;
        Create();
        *values = *x.values;
    }

    Column(Column &&x) : values(x.values)
    {
        size = x.size;
        x.values = nullptr;
    }

    Column &operator=(const Column &x)
    {
        size = x.size;

        if (&x == this)
            return *this;

        delete values;
        Create();

        *values = *x.values;

        return *this;
    }

    Column &operator=(Column &&x)
    {
        this->size = x.size;

        if (&x == this)
            return *this;

        delete values;
        Create();

        values = x.values;
        x.values = nullptr;

        return *this;
    }

    Column operator+(const Column &right) const
    {
        Column res(size);
        for (int i = 0; i < size; ++i)
        {
            res.set(i, get(i) + right.get(i));
        }

        return res;
    }

    Column operator-(const Column &right) const
    {
        Column res(size);
        for (int i = 0; i < size; ++i)
        {
            res.set(i, get(i) - right.get(i));
        }

        return res;
    }
};


#endif //MPI_COLUMN_H
