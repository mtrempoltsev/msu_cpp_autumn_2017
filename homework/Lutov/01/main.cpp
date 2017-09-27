#include "matrix.hpp"
#include "benchmark.hpp"

#include <iostream>
#include <string>

int
main(int argc, char **argv)
{
  matrix m = genetare_matrix();
  if (argc < 2 || argv[1] != std::string("--only-cols")) {
    benchmark("Sum by rows", 500, *m, sum_by_rows);
  }

  if (argc < 2 || argv[1] != std::string("--only-rows")) {
    benchmark("Sum by columns", 500, *m, sum_by_columns);
  }

  return 0;
}
