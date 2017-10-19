#include <algorithm>
#include <cstdlib>
#include <functional>
#include <ios>
#include <iostream>
#include <vector>
#include <valarray>
#include <utility>

// Vector

template<typename value_type>
struct Vector : public std::vector<value_type> {
  static const value_type EPS;

  value_type
  operator[](size_t i) const {
    if (i < this->size()) {
      return std::vector<value_type>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  value_type &
  operator[](size_t i) {
    if (i < this->size()) {
      return std::vector<value_type>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Vector(const std::vector<value_type> &value)
  {
    std::vector<value_type>::operator=(value);
  };

  Vector() = default;

  Vector(Vector<value_type> &&) = default; // Move constructor
  Vector(const Vector<value_type> &) = default; // Copy constructor

  Vector<value_type> &
  operator=(Vector<value_type> &&) = default; // Move operator

  Vector<value_type> &
  operator=(const Vector<value_type> &) = default; // Copy operator

  Vector(const std::initializer_list<value_type> &elems)
  {
    for (auto elem : elems) {
      this->push_back(elem);
    }
  }

  static value_type
  dot(const Vector &a, const Vector &b) {
    if (a.size() != b.size()) {
      throw std::runtime_error("Mismatch vector length for dot product");
    } else {
      value_type result = 0;
      for (size_t i = 0; i < a.size(); ++ i) {
        result += a[i] * b[i];
      }
      return result;
    }
  }

  static int
  compare(const Vector &a, const Vector &b) {
    for (size_t i = 0; i < a.size() && i < b.size(); ++ i) {
      if (a[i] - b[i] > Vector::EPS) {
        return 1;
      } else if (a[i] - b[i] < -Vector::EPS) {
        return -1;
      }
    }

    if (a.size() < b.size()) {
      return -1;
    } else if (a.size() > b.size()) {
      return 1;
    } else {
      return 0;
    }
  }
};

template<>
const double Vector<double>::EPS = 1e-6;

template<typename value_type>
bool
operator==(const Vector<value_type> &a, const Vector<value_type> &b)
{
  return Vector<value_type>::compare(a, b) == 0;
}

template<typename value_type>
bool
operator!=(const Vector<value_type> &a, const Vector<value_type> &b)
{
  return Vector<value_type>::compare(a, b) != 0;
}

// Matrix

template<typename value_type>
struct Matrix : public std::vector<Vector<value_type>>
{
  const static value_type EPS;

  const size_t rows;
  const size_t cols;

  Matrix(size_t _rows, size_t _cols) :
    rows(_rows),
    cols(_cols)
  {
    this->resize(rows);
    for (auto &row : *this) {
      row.resize(cols);

      for (auto &elem : row) {
        elem = 0;
      }
    }
  }

  Matrix(const Matrix<value_type> &other) = default; // Copy constructor

  Matrix(Matrix<value_type> &&) = default; // Move constructor


  Matrix(const std::initializer_list<Vector<value_type>> &elems) :
    rows(elems.size()),
    cols(elems.begin() != elems.end() ? elems.begin()->size() : 0)
  {
    for (const auto &elem : elems) {
      this->push_back(elem);
    }

    if (std::any_of(this->begin(), this->end(), [this](const Vector<value_type> &row){ return row.size() != this->cols; })) {
      throw std::runtime_error("Rows with wrong elem count");
    }
  }

  Matrix<value_type> &
  operator=(const Matrix<value_type> &other) // Copy operator
  {
    const_cast<size_t &>(rows) = other.rows;
    const_cast<size_t &>(cols) = other.cols;

    std::vector<Vector<value_type>>::operator=(other);

    return *this;
  }

  Matrix<value_type> &
  operator=(Matrix<value_type> &&) = default; // Move operator

  const Vector<value_type> &
  operator[](size_t i) const {
    if (i < this->size()) {
      return std::vector<Vector<value_type>>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Vector<value_type> &
  operator[](size_t i) {
    if (i < this->size()) {
      return std::vector<Vector<value_type>>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Matrix<value_type> &
  operator*=(value_type b) {
    for (auto &row : *this) {
      for (auto &e : row) {
        e *= b;
      }
    }
    return *this;
  };

};

template<typename value_type>
Vector<value_type>
operator*(const Matrix<value_type> &A, const Vector<value_type> &b)
{
  auto result = Vector<value_type>();

  for (const auto &row : A) {
    result.push_back(Vector<value_type>::dot(row, b));
  }

  return result;
};

template<typename value_type>
Matrix<value_type>
operator*(const Matrix<value_type> &A, value_type b)
{
  Matrix<value_type> result = A;
  result = A;
  result *= b;
  return result;
}

// Tests

void check(bool value)
{
  if (!value) {
    std::cerr << "error" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    std::cout << ".";
  }
}

using Block = std::function<void ()>;

void
raises(const Block &block) {
  bool raises = false;
  try {
    block();
  } catch(const std::runtime_error &) {
    raises = true;
  }
  check(raises);
}

void
check_size()
{
  std::cout << "check_size";

  Matrix<double> m(3, 4);

  check(m.rows == 3);
  check(m.cols == 4);

  std::cout << "OK" << std::endl;
}

void
check_init()
{
  std::cout << "check_init";

  Matrix<double> m(3, 4);

  check(m.rows == 3);
  check(m.cols == 4);

  for (size_t i = 0; i < m.rows; ++ i) {
    for (size_t j = 0; j < m.cols; ++ j) {
      check(fabs(m[i][j]) <= Vector<double>::EPS);
    }
  }

  m = {{1, 2}, {3, 4}};

  check(m.rows == 2);
  check(m.cols == 2);

  check(fabs(m[0][0] - 1) <= Vector<double>::EPS);
  check(fabs(m[0][1] - 2) <= Vector<double>::EPS);
  check(fabs(m[1][0] - 3) <= Vector<double>::EPS);
  check(fabs(m[1][1] - 4) <= Vector<double>::EPS);

  raises([]{ Matrix<double>({{1, 2}, {3}}); });

  std::cout << "OK" << std::endl;
}

void
check_get_set()
{
  std::cout << "check_get_set";

  Matrix<double> m(2, 3);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  check(fabs(m[0][0] - 1) <= Vector<double>::EPS);
  check(fabs(m[0][1] - 2) <= Vector<double>::EPS);
  check(fabs(m[0][2] - 3) <= Vector<double>::EPS);
  check(fabs(m[1][0] - 4) <= Vector<double>::EPS);
  check(fabs(m[1][1] - 5) <= Vector<double>::EPS);
  check(fabs(m[1][2] - 6) <= Vector<double>::EPS);

  m[1][2] = 100;

  check(fabs(m[1][2] - 100) <= Vector<double>::EPS);

  std::cout << "OK" << std::endl;
}

void
check_raises()
{
  std::cout << "check_raises";

  Matrix<double> m(2, 3);

  raises([&m]{ m[-1][0]; });
  raises([&m]{ m[3][0]; });
  raises([&m]{ m[0][-1]; });
  raises([&m]{ m[0][3]; });

  raises([&m]{ m[-1][0] = 10; });
  raises([&m]{ m[3][0] = 10; });
  raises([&m]{ m[0][-1] = 10; });
  raises([&m]{ m[0][3] = 10; });

  std::cout << "OK" << std::endl;
}

void
check_equal()
{
  std::cout << "check_equal";

  Matrix<double> m1(2, 3), m2(2, 3), m3(4, 4);

  // Empty matrix
  check(m1 == m2);
  check(!(m1 != m2));

  check(!(m1 == m3));
  check(m1 != m3);

  // Uniq matrix
  m1[1][0] = 10;
  check(!(m1 == m2));
  check(m1 != m2);

  check(!(m1 == m3));
  check(m1 != m3);

  // Not uniq matrix
  m2[1][0] = 10;
  check(m1 == m2);
  check(!(m1 != m2));

  check(!(m1 == m3));
  check(m1 != m3);

  std::cout << "OK" << std::endl;
}

void
check_multiply()
{
  std::cout << "check_multiply";

  Matrix<double> m = {{1, 2},
              {3, 4},
              {5, 6}};
  Vector<double> v = {1, 2};

  check(m * v == Vector<double>({5, 11, 17}));

  check(m * 2.0 == Matrix<double>({{2, 4},
                                 {6, 8},
                                 {10, 12}}));

  check(m == Matrix<double>({{1, 2},
                             {3, 4},
                             {5, 6}}));
  m *= 2;
  check(m == Matrix<double>({{2, 4},
                             {6, 8},
                             {10, 12}}));

  std::cout << "OK" << std::endl;
}

// Main

int
main()
{
  std::ios::sync_with_stdio(false);

  check_size();
  check_init();
  check_get_set();
  check_raises();
  check_equal();
  check_multiply();

  return 0;
}
