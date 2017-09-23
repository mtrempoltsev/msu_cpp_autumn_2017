#include <cstdlib>
#include "config.h"
#include "measure.h"

long
sum_by_rows(const int m[N][N])
{
    long s = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            s += m[i][j];
        }
    }
    return s;
}

int
main()
{
    std::cout << "Average time: "
              << measure_avg_time(sum_by_rows)
              << " us" << std::endl;
}
