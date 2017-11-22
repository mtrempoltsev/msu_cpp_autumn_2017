# include "iterator.h"

template <class T, class Alloc = std::allocator<T>>
class  Vector
{
  private:
    T* data;
    size_t size;
    size_t capacity;
  public:
    using iterator = Iterator<T>;
    using Riterator = Reverse_Iterator<T>;

    Vector()
    {
      size = 0;
      capacity = 0;
    }

    explicit Vector(size_t count)
    {
      size = count;
      capacity = count * 2;
    }

    explicit Vector(size_t count, const T& defaultValue)
    {
      size = count;
      capacity = count * 2;
      data = new T[capacity];
      for (size_t i = 0; i < size; ++i){
        data[i] = defaultValue;
      }
    }

    T& operator[](size_t position)
    {
      if (position >= size)
        throw ("Out of range");
      return this -> data[position];
    }

    size_t Size() const noexcept {
      return size;
    }

    size_t Capacity_() const noexcept{
      return capacity;
    }

    Iterator<T> begin() noexcept
    {
      return Iterator<T> (this->data);
    }

    Iterator<T> end() noexcept
    {
      return Iterator<T>(this->data + this->size);
    }

    Reverse_Iterator<T> rbegin() noexcept
    {
      return Reverse_Iterator<T>(this->data + this->size - 1);
    }

    Reverse_Iterator<T> rend() noexcept
    {
      return Reverse_Iterator<T>(this->data - 1);
    }

    void resize(size_t newSize)
    {
      *this = move(Vector(newSize));
    }

    void resize(size_t newSize, const T& defaultValue)
    {
      *this = move(Vector(newSize, defaultValue));
    }

    void empty()
    {
      return this->size == 0;
    }

    void clear()
    {
        *this = move(Vector());
    }

    void push_back(const T& value)
    {
      if(this->data == nullptr)
      {
        *this = move(Vector(8));
        this->size = 0;
      }
      if(this->size == this->capacity)
      {
        auto time_vec = move(*this);
        this->resize(this->capacity);
        for (size_t j = 0; j < this->size; j++)
          this->data[j] = time_vec[j];
      }
      this->data[this->size++] = value;
    }

    void pop_back()
    {
      if (size == 0)
        throw "Out of range";
      else if (size == 1)
        this->clear();
      else
        size--;
    }

};
