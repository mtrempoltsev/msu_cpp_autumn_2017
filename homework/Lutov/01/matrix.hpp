#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <array>
#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <functional>
#include <memory>
#include <random>

template <typename value_type, size_t rows, size_t cols>
using raw_matrix = std::array<std::array<value_type, rows>, cols>;

template <typename value_type, size_t rows, size_t cols>
using matrix = std::shared_ptr<raw_matrix<value_type, rows, cols>>;

template <typename value_type, size_t rows, size_t cols>
matrix<value_type, rows, cols>
genetare_matrix()
{
  auto presult = matrix<value_type, rows, cols>(new raw_matrix<value_type, rows, cols>);

  std::default_random_engine generator;
  std::uniform_int_distribution<intmax_t> distribution(LLONG_MIN, LLONG_MAX);

  for (auto &row : *presult) {
    for (auto &val : row) {
      val = distribution(generator);
    }
  }

  return presult;
}

template <typename value_type, size_t rows, size_t cols>
auto
sum_by_rows(const matrix<value_type, rows, cols> &pm)
{
  value_type sum = 0;

  for (const auto &row : *pm) {
    for (const auto &val : row) {
      sum += val;
    }
  }

  return sum;
}

template <typename value_type, size_t rows, size_t cols>
auto
sum_by_columns(const matrix<value_type, rows, cols> &pm)
{
  const auto &m = *pm;
  value_type sum = 0;

  for (size_t j = 0; j < cols; ++j) {
    for (size_t i = 0; i < rows; ++i) {
      sum += m[i][j];
    }
  }

  return sum;
}

template <typename value_type, size_t rows, size_t cols>
using sum_function = value_type(const matrix<value_type, rows, cols> &);

#endif
