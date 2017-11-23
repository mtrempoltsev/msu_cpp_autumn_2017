# include "vector.h"
#include <cmath>
//# include <iostream>

void check_bool(bool s) {
    if (!s)
      throw "Error";
}

template<class T>
void check_value(T res, T result) {
    if (fabs( res - result) > 0.00001)
      throw "Error";
}

int main()
{
  try
  {
    // Проверки
    Vector<int> A(3,2);
    check_value<int>(A[0], 2);
    check_value<int>(A[1], 2);
    check_value<int>(A[2], 2);
    A.resize(6,3);
    A.push_back(4);
    check_value<int>(A[6], 4);
    check_value<int>(A.Size(), 7);
    A.pop_back();
    check_value<int>(A.Size(), 6);
    Iterator<int> it_begin = A.begin();

    for (size_t i = 0; i < A.Size(); i++, ++it_begin) {
      check_bool(*it_begin == A[i]);
    }

    Reverse_Iterator<int> it_rbegin = A.rbegin();

    //Reverse_Iterator<int> it_rend = A.rend();
    for (size_t i = 0; i < A.Size(); i++, ++it_rbegin) {
      check_bool(*it_rbegin == A[A.Size() - i - 1]);
    }

    A.clear();
    check_value<int>(A.Size(), 0);
  }
  catch(const char* str) {
    cout << str << endl;
    return 1;
  }
  return 0;
}
