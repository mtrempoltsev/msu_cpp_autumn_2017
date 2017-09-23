#include <cstdlib>
#include "measure.h"

long
sum_by_columns(int n, const int *m)
{
    long s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s += m[j*n + i];
        }
    }
    return s;
}

int
main()
{
    std::cout << "Average time: " << measure(sum_by_columns) << " us" << std::endl;
}
