#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "Matrix.hpp"
#include "Timer.hpp"

using SumType = int;

inline SumType fill(size_t i)
{
    return i * i;
}

[[noreturn]] void usage(const char* cmd)
{
    using namespace std;

    cerr << "usage: " << cmd << " <N> <col|row>" << endl;
    exit(1);
}

int main(int argc, char* argv[])
{
    using namespace std;

    if (argc != 3) {
        usage(argv[0]);
    }

    size_t size = atoi(argv[1]);

    bool byColumn = false;
    if (string("col") == argv[2]) {
        byColumn = true;
    } else if (string("row") == argv[2]) {
        byColumn = false;
    } else {
        usage(argv[0]);
    }

    Matrix<SumType> array(size);

    // filling array
    for (size_t j = 0; j < size; ++j)
        for (size_t i = 0; i < size; ++i)
            array[j][i] = fill(i + j);

    volatile SumType sum = 0;
    {
        Timer timer;

        if (byColumn) {
            // sum by column
            for (size_t i = 0; i < size; ++i)
                for (size_t j = 0; j < size; ++j)
                    sum += array[j][i];
        } else {
            // sum by row
            for (size_t j = 0; j < size; ++j)
                for (size_t i = 0; i < size; ++i)
                    sum += array[j][i];
        }
    }

    return 0;
}
