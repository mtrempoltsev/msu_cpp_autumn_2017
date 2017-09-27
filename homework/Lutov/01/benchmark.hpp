#ifndef BENCHMAR_HPP
#define BENCHMAR_HPP

#include "matrix.hpp"

#include <ctime>
#include <string>

time_t
benchmark(const std::string &, ssize_t, const raw_matrix &, sum_function);

#endif
