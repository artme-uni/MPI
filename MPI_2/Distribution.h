#ifndef MPI_DISTRIBUTION_H
#define MPI_DISTRIBUTION_H


class Distribution
{
public:
    int n;

    int PR_count;
    int PR_rank;

    int *index_M;
    int *count_M;

    int *index_C;
    int *count_C;


    Distribution(int count, int rank, int n) : PR_count(count), PR_rank(rank), n(n)
    {
        index_M = new int[PR_count];
        count_M = new int[PR_count];

        index_C = new int[PR_count];
        count_C = new int[PR_count];

        create();
    }

private:
    void create()
    {
        int rest_rows = n;
        int row_number = n / PR_count;

        count_M[0] = row_number * n;
        index_M[0] = 0;

        for (int i = 1; i < PR_count; i++)
        {
            rest_rows -= row_number;
            row_number = rest_rows / (PR_count - i);
            count_M[i] = row_number * n;
            index_M[i] = index_M[i - 1] + count_M[i - 1];
        }

        for (int i = 0; i < PR_count; i++)
        {
            index_C[i] = index_M[i] / n;
            count_C[i] = count_M[i] / n;
        }
    }
};


#endif //MPI_DISTRIBUTION_H
