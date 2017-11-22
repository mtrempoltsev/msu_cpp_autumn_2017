# include <iostream>
using namespace std;

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
  private:
    T* ptr;

  public:
    explicit Iterator<T>(T* ptr_)
    {
      ptr = ptr_;
    }

    Iterator<T> operator ++()
    {
      ptr++;
      return *this;
    }

    Iterator<T> operator --()
    {
      ptr--;
      return *this;
    }

    bool operator == (const Iterator& tmp)
    {
      return ptr == tmp.ptr;
    }

    bool operator != (const Iterator& tmp)
    {
      return ptr != tmp.ptr;
    }

    T& operator*()
    {
      return *ptr;
    }

    T* operator->()
    {
      return ptr;
    }
};

template <class T>
class Reverse_Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
  private:
    T* ptr;
  public:
    explicit Reverse_Iterator<T>(T* ptr_)
    {
      ptr = ptr_;
    }

    Reverse_Iterator<T> operator ++()
    {
      ptr--;
      return *this;
    }

    Iterator<T> operator --()
    {
      ptr++;
      return *this;
    }

    bool operator == (const Reverse_Iterator& tmp)
    {
      return ptr == tmp.ptr;
    }

    bool operator != (const Reverse_Iterator& tmp)
    {
      return ptr != tmp.ptr;
    }

    T& operator*()
    {
      return *ptr; // return this -> ptr ?
    }

    T* operator->()
    {
      return ptr;
    }

};
