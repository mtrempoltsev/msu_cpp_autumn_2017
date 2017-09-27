#include "matrix.hpp"

#include <climits>
#include <iostream>
#include <random>

matrix
genetare_matrix()
{
  auto presult = matrix(new raw_matrix);
  raw_matrix &result = *presult;
  const ssize_t shape_x = result[0].size();
  const ssize_t shape_y = result.size();

  std::default_random_engine generator;
  std::uniform_int_distribution<intmax_t> distribution(LLONG_MIN, LLONG_MAX);

  for (ssize_t i = 0; i < shape_y; ++i) {
    for (ssize_t j = 0; j < shape_x; ++j) {
      result[i][j] = distribution(generator);
    }
  }

  return presult;
}

int
sum_by_rows(const raw_matrix &m)
{
  intmax_t sum = 0;
  const ssize_t shape_x = m[0].size();
  const ssize_t shape_y = m.size();

  for (ssize_t i = 0; i < shape_y; ++i) {
    for (ssize_t j = 0; j < shape_x; ++j) {
      sum += m[i][j];
    }
  }

  return sum;
}

int
sum_by_columns(const raw_matrix &m)
{
  intmax_t sum = 0;
  const ssize_t shape_x = m[0].size();
  const ssize_t shape_y = m.size();

  for (ssize_t j = 0; j < shape_x; ++j) {
    for (ssize_t i = 0; i < shape_y; ++i) {
      sum += m[i][j];
    }
  }

  return sum;
}
