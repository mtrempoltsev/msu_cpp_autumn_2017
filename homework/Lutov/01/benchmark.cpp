#include "benchmark.hpp"
#include "timer.hpp"

#include <cstdlib>
#include <iostream>

time_t
benchmark(const std::string &sum_type, ssize_t count, const raw_matrix &m, sum_function f)
{
  std::cout << sum_type << std::endl;

  auto t = Timer(count);
  for (ssize_t i = 0; i < count; ++i) {
    f(m);
  }

  return t.diff();
}
