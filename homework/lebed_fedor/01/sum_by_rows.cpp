#include <cstdlib>
#include "config.h"
#include "measure.h"

// returns sum of all matrix element
long sum_by_rows(const int m[DIM][DIM])
{
    long s = 0;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            s += m[i][j];
        }
    }
    return s;
}

int main()
{
    std::cout << "Average time: "
              << measure_avg_time(sum_by_rows)
              << " us" << std::endl;
}
