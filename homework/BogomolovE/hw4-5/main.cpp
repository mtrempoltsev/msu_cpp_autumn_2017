#include <iostream>
#include <vector>


//Complimentary class for acessing matrix rows
template <class T>
class Row
{
  T *arr;
  size_t len;
public:
  Row<T> (T* arr_, size_t len_)
  {
    arr = arr_;
    len = len_;
  }
  // Overoloaded operator [] for getting value
  const T operator[](const size_t &y) const
  {
    if (y > this->len - 1){
      exit(1);
    }
    return this->arr[y];
  }

  // Overoloaded operator [] for setting value
  T& operator[](const size_t &y)
  {
    if (y > this->len - 1){
      exit(1);
    }
    T &tmp = this->arr[y];
    return tmp;
  }
};


//Main Matrix class
template <class T>
class Matrix
{

    size_t rows;
    size_t cols;
    T **arr;

public:
    template <class U>
    friend Matrix<U> operator*(const Matrix<U> &mat, const U &y);

    template <class U>
    friend Matrix<U> operator*(const U &y, const Matrix<U> &mat);

    template <class U>
    friend Matrix<U> operator*(const Matrix<U> &mat, const std::vector<U> &y);

    template <class U>
    friend bool operator==(const Matrix<U> &lmat, const Matrix<U> &rmat);

    template <class U>
    friend bool operator!=(const Matrix<U> &lmat, const Matrix<U> &rmat);

    //Init Constructor
    Matrix (size_t rows_, size_t cols_)
    {
      std::cout << "!!!" << std::endl;
        cols = cols_;
        rows = rows_;
        arr = new T*[rows];
        for(auto i = 0; i < rows; ++i)
            arr[i] = new T[cols];
    }

    //Copy Constructor
    Matrix (const Matrix &mat)
    {
        std::cout << "copy !!!" << std::endl;
        cols = mat.cols;
        rows = mat.rows;
        arr = new T*[rows];
        for(auto i = 0; i < rows; ++i){
            arr[i] = new T[cols];
            std::copy(mat.arr[i], mat.arr[i] + cols, arr[i]);
        }
    }

    //Move Constructor
    Matrix (const Matrix &&mat)
    {
        std::cout << "move !!!" << std::endl;
        cols = mat.cols;
        rows = mat.rows;
        arr = new T*[rows];
        for(auto i = 0; i < rows; ++i){
            arr[i] = new T[cols];
            std::move(mat.arr[i], mat.arr[i] + cols, arr[i]);
        }
    }

    //Copy Operator
    Matrix& operator=(const Matrix &mat)
    {
      if ((cols != mat.cols) || (rows != mat.rows)){
        std::cout << "Wrong sizes for copy assignment!" << std::endl;
        exit(1);
      }

      for(auto i = 0; i < rows; ++i){
          std::copy(mat.arr[i], mat.arr[i] + cols, arr[i]);
      }
    }

    //Move Operator
    Matrix& operator=(const Matrix &&mat)
    {
      if ((cols != mat.cols) || (rows != mat.rows)){
        std::cout << "Wrong sizes for move assignment!" << std::endl;
        exit(1);
      }

      for(auto i = 0; i < rows; ++i){
          std::move(mat.arr[i], mat.arr[i] + cols, arr[i]);
      }
    }


    void output()
    {
      for (auto i = 0; i < this->rows; ++i){
        for(auto j = 0; j < this->cols; ++j){
          std::cout << this->arr[i][j] << " ";
        }
        std::cout<<std::endl;
      }
    }

    size_t getColCount()
    {
        return cols;
    }

    size_t getRowCount()
    {
        return rows;
    }


    // Overoloaded operator [] for getting value
    const Row<T> operator[](const size_t &y) const
    {
        if (y > this->rows - 1){
          exit(1);
        }
        double *arr = this->arr[y];

        //Returning constant object
        return Row<T>(arr, this->cols);
    }
    // Overoloaded operator [] for setting value
    Row<T> operator[](const size_t &y)
    {
        if (y > this->rows  - 1){
          exit(1);
        }
        T *arr = this->arr[y];

        return Row<T>(arr, this->cols);
    }

      // Destructor
      ~Matrix()
      {
        std::cout << "~~~" << std::endl;
        for(auto i = 0; i < rows; ++i)
            delete[] arr[i];
        delete[] arr;
      }


};


// Operator == for two matrices
template <class T>
bool operator==(const Matrix<T> &lmat, const Matrix<T> &rmat)
{
    if ((lmat.cols != rmat.cols) || (lmat.rows != rmat.rows)){
        std::cout << "Wrong sizes for comparing" << std::endl;
        exit(1);
    }

    bool flag = true;
    for(auto i = 0; i < lmat.rows; ++i){
      for(auto j = 0; j < lmat.cols; ++j){
        if (lmat[i][j] != rmat[i][j]){
          flag = false;
          break;
        }
        if (!flag){break;}
      }
    }
    //If all elements are same then return TRUE value
    return flag;


}

// Operator != for two matrices
// This is an inversion of ==
template <class T>
bool operator!=(const Matrix<T> &lmat, const Matrix<T> &rmat)
{

    bool flag;
    flag = !(lmat == rmat);
    return flag;
  }

// Matrix multiplying on constant at the right
template <class T>
Matrix<T> operator*(const Matrix<T> &mat, const T &y)
{
  Matrix<T>  z = Matrix<T>(mat.rows, mat.cols);
  for(auto i = 0; i < mat.rows; ++i){
    for(auto j = 0; j < mat.cols; ++j){
      z.arr[i][j] = mat.arr[i][j] * y;
    }
  }
  return z;
}

// Operator * for multiplying at the right
template <class T>
Matrix<T> operator*(const Matrix<T> &mat, const std::vector<T> &y)
{
    if (mat.cols != y.size()){
        std::cout << "Wrong sizes" << std::endl;
        return mat;
    }
    Matrix<T> z = Matrix<T>(mat.rows, 1);
    for(auto i = 0; i < mat.rows; ++i)
    {
        z.arr[i][0] = 0.0;
        for(auto j = 0; j < mat.cols; ++j){
            z.arr[i][0] +=  mat.arr[i][j] * y[j];

        }
    }

    return z;
  }

// Matrix multiplying on constant at the left
template <class T>
Matrix<T> operator*(const T &y, const Matrix<T> &mat)
{
  Matrix<T>  z = Matrix<T>(mat.rows, mat.cols);
  for(auto i = 0; i < mat.rows; ++i)
  {
    for(auto j = 0; j < mat.cols; ++j){
      z.arr[i][j] = mat.arr[i][j] * y;
    }
  }
  return z;
}


//Test fucntion
void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
    Matrix<int> m(2,3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    check(m[0][0] == 1);

    check(m[0][1] == 2);

    check(m[0][2] == 3);

    check(m[1][0] == 4);

    check(m[1][1] == 5);

    check(m[1][2] == 6);


    m[1][2] = 100;

    check(m[1][2] == 100);

    std::cout<< "If there's no error then OK!" << std::endl;
}


//My test function
void MyTest()
{

  std::cout << "\n!!! --- means that constructor has worked" <<std::endl;
  std::cout << "~~~ --- means that destructor has worked\n" <<std::endl;

  const size_t N = 5;
  const size_t M = 6;
  Matrix<double> mat = Matrix<double>(M,N);
  std::vector<double> vec;

  //Initialize one vector
  std::cout << "\nVector vec:" <<std::endl;
  for (auto i = 0; i < N; ++i){
    vec.push_back(1.0);
    std::cout << vec[i] << std::endl;
  }

  //Initialize and output one matrix
  std::cout << "\nMatrix mat:" <<std::endl;
  for (auto i = 0; i < M; ++i){
    for(auto j = 0; j < N; ++j){
      auto  tmp = (i+1) * (j+1) * 2.0;
      mat[i][j] = tmp;
    }
  }
  mat.output();

  //Multiply matrix on vector and output
  std::cout << "\nmul_mat = mat * vec:" <<std::endl;
  Matrix<double> mul_mat = mat * vec;
  mul_mat.output();

  //Multiply matrix on constant at the both sides
  std::cout << "\nnew_mat = 2.0* mat * 2.0:" <<std::endl;
  Matrix<double> new_mat = 2.0*mat*2.0;
  new_mat.output();

  // Testing comparing operations
  bool tmp;
  std::cout << "\nmat == mat?:" <<std::endl;
  tmp = (mat == mat);
  std::cout << tmp << std::endl;
  std::cout << "\nnew_mat != mat?:" <<std::endl;
  tmp = (mat != new_mat);
  std::cout << tmp << std::endl;

  //Testing copy operator
  std::cout << "\ncopy_mat = mat:" <<std::endl;
  Matrix<double> copy_mat = Matrix<double>(M,N);
  copy_mat = mat;
  std::cout << "\ncopy_mat:" <<std::endl;
  copy_mat.output();


  //Testing move operator
  std::cout << "\nmove_mat = Matrix(move(copy_mat)):" <<std::endl;
  Matrix<double> move_mat = Matrix<double>(std::move(copy_mat));
  std::cout << "\nmove_mat:" <<std::endl;
  copy_mat.output();

  //Testing move operator
  std::cout << "\nmove_mat = move(mat):" <<std::endl;

  move_mat = std::move(mat);
  std::cout << "\nmove_mat:" <<std::endl;
  copy_mat.output();

}

int main(void)
{

  std::cout << "MyTest():" << std::endl;
  MyTest();
  std::cout << "\ncheckGetSet():"<< std::endl;
  checkGetSet();

  return 0;

}
