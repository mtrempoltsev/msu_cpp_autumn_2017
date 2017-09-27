#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <array>
#include <cinttypes>
#include <cstdlib>
#include <functional>
#include <memory>

const ssize_t SHAPE_X = 1000;
const ssize_t SHAPE_Y = 1000;
typedef std::array<std::array<intmax_t, SHAPE_X>, SHAPE_Y> raw_matrix;
typedef std::shared_ptr<raw_matrix> matrix;

matrix
genetare_matrix();

int
sum_by_columns(const raw_matrix &);

int
sum_by_rows(const raw_matrix &);

typedef std::function<intmax_t(const raw_matrix &)> sum_function;

#endif
