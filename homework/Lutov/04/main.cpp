#include <algorithm>
#include <cstdlib>
#include <functional>
#include <ios>
#include <iostream>
#include <vector>
#include <valarray>
#include <utility>

// Vector

struct Vector : public std::vector<double> {
  double
  operator[](size_t i) const {
    if (i < this->size()) {
      return (*this).std::vector<double>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  double &
  operator[](size_t i) {
    if (i < this->size()) {
      return (*this).std::vector<double>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Vector(const std::vector<double> &value)
  {
    this->std::vector<double>::operator=(value);
  };

  Vector()
  {
  };

  Vector(const std::initializer_list<double> &elems)
  {
    for (auto elem : elems) {
      this->push_back(elem);
    }
  }

  static double
  dot(const Vector &a, const Vector &b) {
    if (a.size() != b.size()) {
      throw std::runtime_error("Mismatch vector length for dot product");
    } else {
      double result = 0;
      for (size_t i = 0; i < a.size(); ++ i) {
        result += a[i] * b[i];
      }
      return result;
    }
  }

  static int
  compare(const Vector &a, const Vector &b);
};

bool
operator==(const Vector &a, const Vector &b)
{
  return Vector::compare(a, b) == 0;
}

bool
operator!=(const Vector &a, const Vector &b)
{
  return Vector::compare(a, b) != 0;
}

// Matrix

struct Matrix : public std::vector<Vector>
{
  const static double EPS;

  const size_t rows;
  const size_t cols;

  Matrix(size_t _rows, size_t _cols) :
    rows(_rows),
    cols(_cols)
  {
    this->resize(this->rows);
    for (auto &row : *this) {
      row.resize(this->cols);

      for (auto &elem : row) {
        elem = 0;
      }
    }
  }

  Matrix(const Matrix &other) :
    rows(other.rows),
    cols(other.cols)
  {
    this->std::vector<Vector>::operator=(other);
  }

  Matrix(const std::initializer_list<Vector> &elems) :
    rows(elems.size()),
    cols(elems.begin() != elems.end() ? elems.begin()->size() : 0)
  {
    for (const auto &elem : elems) {
      this->push_back(elem);
    }

    if (std::any_of(this->begin(), this->end(), [this](const Vector &row){ return row.size() != this->cols; })) {
      throw std::runtime_error("Rows with wrong elem count");
    }
  }

  Matrix &
  operator=(const Matrix &other)
  {
    const_cast<size_t &>(this->rows) = other.rows;
    const_cast<size_t &>(this->cols) = other.cols;

    this->std::vector<Vector>::operator=(other);

    return *this;
  }

  Matrix &
  operator=(Matrix &&other)
  {
    const_cast<size_t &>(this->rows) = other.rows;
    const_cast<size_t &>(this->cols) = other.cols;

    this->std::vector<Vector>::operator=(other);

    return *this;
  }

  const Vector &
  operator[](size_t i) const {
    if (i < this->size()) {
      return (*this).std::vector<Vector>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Vector &
  operator[](size_t i) {
    if (i < this->size()) {
      return (*this).std::vector<Vector>::operator[](i);
    } else {
      throw std::runtime_error("Incorrect index");
    }
  }

  Matrix &
  operator*=(double b) {
    for (auto &row : *this) {
      for (auto &e : row) {
        e *= b;
      }
    }
    return *this;
  };

};

const double Matrix::EPS = 1e-6;

int
Vector::compare(const Vector &a, const Vector &b) {
  for (size_t i = 0; i < a.size() && i < b.size(); ++ i) {
    if (a[i] < b[i] - Matrix::EPS) {
      return -1;
    } else if (a[i] > b[i] + Matrix::EPS) {
      return 1;
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


Vector
operator*(const Matrix &A, const Vector &b)
{
  auto result = Vector();

  for (const auto &row : A) {
    result.push_back(Vector::dot(row, b));
  }

  return result;
};

Matrix
operator*(const Matrix &A, double b)
{
  Matrix result = A;
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

  Matrix m(3, 4);

  check(m.rows == 3);
  check(m.cols == 4);

  std::cout << "OK" << std::endl;
}

void
check_init()
{
  std::cout << "check_init";

  Matrix m(3, 4);

  check(m.rows == 3);
  check(m.cols == 4);

  for (size_t i = 0; i < m.rows; ++ i) {
    for (size_t j = 0; j < m.cols; ++ j) {
      check(abs(m[i][j]) <= Matrix::EPS);
    }
  }

  m = {{1, 2}, {3, 4}};

  check(m.rows == 2);
  check(m.cols == 2);

  check(abs(m[0][0] - 1) <= Matrix::EPS);
  check(abs(m[0][1] - 2) <= Matrix::EPS);
  check(abs(m[1][0] - 3) <= Matrix::EPS);
  check(abs(m[1][1] - 4) <= Matrix::EPS);

  raises([]{ Matrix({{1, 2}, {3}}); });

  std::cout << "OK" << std::endl;
}

void
check_get_set()
{
  std::cout << "check_get_set";

  Matrix m(2, 3);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  check(abs(m[0][0] - 1) <= Matrix::EPS);
  check(abs(m[0][1] - 2) <= Matrix::EPS);
  check(abs(m[0][2] - 3) <= Matrix::EPS);
  check(abs(m[1][0] - 4) <= Matrix::EPS);
  check(abs(m[1][1] - 5) <= Matrix::EPS);
  check(abs(m[1][2] - 6) <= Matrix::EPS);

  m[1][2] = 100;

  check(abs(m[1][2] - 100) <= Matrix::EPS);

  std::cout << "OK" << std::endl;
}

void
check_raises()
{
  std::cout << "check_raises";

  Matrix m(2, 3);

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

  Matrix m1(2, 3), m2(2, 3), m3(4, 4);

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

  Matrix m = {{1, 2},
              {3, 4},
              {5, 6}};
  std::vector<double> v = {1, 2};

  check(m * v == Vector({5, 11, 17}));

  check(m * 2 == Matrix({{2, 4},
                         {6, 8},
                         {10, 12}}));

  check(m == Matrix({{1, 2},
                     {3, 4},
                     {5, 6}}));
  m *= 2;
  check(m == Matrix({{2, 4},
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
