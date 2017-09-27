#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "timer.h"

using SumType = int;

inline SumType fill(size_t i)
{
    return i * i;
}

int main(int argc, char* argv[])
{
    using namespace std;

    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <N> <col|row>" << endl;
        exit(1);
    }
    size_t size = atoi(argv[1]);
    bool byColumn = string("col") == argv[2];

    SumType* array;
    try {
        array = new SumType[size * size];
    } catch (bad_alloc) {
        cerr << "new failed" << endl;
        exit(1);
    }

    // filling array
    for (size_t i = 0; i < size * size; ++i) {
        array[i] = fill(i);
    }

    volatile SumType sum = 0;
    {
        Timer timer;

        if (byColumn) {
            // sum by column
            for (size_t i = 0; i < size; ++i)
                for (size_t j = 0; j < size; ++j)
                    sum += array[size * j + i];
        } else {
            // sum by row
            for (size_t j = 0; j < size; ++j)
                for (size_t i = 0; i < size; ++i)
                    sum += array[size * j + i];
        }
    }

    delete[] array;
    return 0;
}
