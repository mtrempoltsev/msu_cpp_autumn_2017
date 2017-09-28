#include "matrix.hpp"
#include "benchmark.hpp"

#include <iostream>
#include <string>

int
main(int argc, char **argv)
{
  auto pm = genetare_matrix<intmax_t, 1000, 1000>();
  bool only_rows = argc >= 2 && argv[1] == std::string("--only-rows");
  bool only_cols = argc >= 2 && argv[1] == std::string("--only-cols");

  if (!only_cols) {
    benchmark("Sum by rows", 500, pm, sum_by_rows);
  }

  if (!only_rows) {
    benchmark("Sum by columns", 500, pm, sum_by_columns);
  }

  return 0;
}
