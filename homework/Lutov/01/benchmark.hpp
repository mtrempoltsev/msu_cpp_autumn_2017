#ifndef BENCHMAR_HPP
#define BENCHMAR_HPP

#include "matrix.hpp"
#include "timer.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

template<typename value_type, size_t rows, size_t cols>
time_t
benchmark(const std::string &sum_type, size_t count, const matrix<value_type, rows, cols> &pm, sum_function<value_type, rows, cols> f)
{
  std::cout << sum_type << std::endl;

  auto t = Timer(count);
  for (size_t i = 0; i < count; ++i) {
    f(pm);
  }

  return t.diff();
}

#endif
