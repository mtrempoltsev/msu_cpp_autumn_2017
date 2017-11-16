#include <cstddef>
#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
struct Vector {
private:

  template <typename reference, typename pointer>
  struct ReverseIterator { // Reverse random-access iterator
  private:
    pointer _data;

  public:
    explicit
    ReverseIterator(pointer data) :
      _data(data)
    {
    }

    ReverseIterator(const ReverseIterator &) = default; // Copy constructor and operator
    ReverseIterator &
    operator=(const ReverseIterator &) = default;

    ReverseIterator(ReverseIterator &&) = default; // Move constructor and operator
    ReverseIterator &
    operator=(ReverseIterator &&) = default;

    // pointer operators
    reference
    operator*()
    {
      return *_data;
    }

    pointer
    operator->()
    {
      return _data;
    }

    auto
    operator+(ptrdiff_t n)
    {
      return ReverseIterator(_data - n);
    }

    auto
    operator-(ptrdiff_t n)
    {
      return ReverseIterator(_data + n);
    }

    ReverseIterator &
    operator++()
    {
      -- _data;
      return *this;
    }

    ReverseIterator
    operator++(int)
    {
      return ReverseIterator(_data --);
    }

    ReverseIterator<reference, pointer> &
    operator--()
    {
      ++ _data;
      return *this;
    }

    ReverseIterator
    operator--(int)
    {
      return ReverseIterator(_data ++);
    }

    bool
    operator==(const ReverseIterator &other)
    {
      return _data == other._data;
    }

    bool
    operator!=(const ReverseIterator &other)
    {
      return _data != other._data;
    }
  };

public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = ReverseIterator<reference, pointer>;
  using const_reverse_iterator = ReverseIterator<const_reference, const_pointer>;
  using difference_type = ptrdiff_t;
  using size_type = size_t;

private:
  const static ptrdiff_t VECTOR_INIT_CAPACITY = 32;
  ptrdiff_t _capacity;
  ptrdiff_t _size;
  pointer _data;

public:
  void
  clear()
  {
    if (_data != nullptr) {
      for (ptrdiff_t i = 0; i < _size; ++ i) {
        _data[i].~value_type();
      }
      free(_data);
    }

    _capacity = 0;
    _size = 0;
    _data = nullptr;
  }

  Vector() :

    _capacity(VECTOR_INIT_CAPACITY),
    _size(0),
    _data(static_cast<pointer>(malloc(sizeof(value_type) * _capacity)))
  {
  }

  Vector(const std::initializer_list<value_type> &lst) :
    _capacity(lst.size()),
    _size(lst.size()),
    _data(static_cast<pointer>(malloc(sizeof(value_type) * _capacity)))
  {
    ptrdiff_t i = 0;
    for (const auto &elem : lst) {
      new (_data + i) value_type(elem);
      ++ i;
    }
  }

  explicit
  Vector(size_t size) :
    _capacity(size),
    _size(size),
    _data(static_cast<pointer>(malloc(sizeof(value_type) * _capacity)))
  {
    for (ptrdiff_t i = 0; i < _size; ++ i) {
      new (_data + i) value_type();
    }
  }

  Vector(const Vector &other) :
    _capacity(other._capacity),
    _size(other._size),
    _data(static_cast<pointer>(malloc(sizeof(value_type) * _capacity)))
  {
    for (ptrdiff_t i = 0; i < _size; ++ i) {
      new (_data + i) value_type(other[i]);
    }
  }

  Vector(Vector &&other) :
    _capacity(other._capacity),
    _size(other._size),
    _data(other._data)
  {
    if (this != &other) {
      other._capacity = 0;
      other._size = 0;
      other._data = nullptr;
    }
  }

  ~Vector()
  {
    clear();
  }

  Vector &
  operator=(const Vector &other)
  {
    if (this != &other) {
      clear();
      _capacity = other._capacity;
      _size = other._size;
      _data = static_cast<pointer>(malloc(sizeof(value_type) * _capacity));
      for (ptrdiff_t i = 0; i < _size; ++ i) {
        new (_data + i) value_type(other[i]);
      }
    }
    return *this;
  }

  Vector &
  operator=(Vector &&other)
  {
    if (this != &other) {
      clear();
      _capacity = other._capacity;
      other._capacity = 0;
      _size = other._size;
      other._size = 0;
      _data = other._data;
      other._data = nullptr;
    }
    return *this;
  }

  inline reference
  operator[](size_t i) {
    return _data[i];
  }

  inline const_reference
  operator[](size_t i) const {
    return _data[i];
  }

  inline size_t
  size() const {
    return _size;
  }

  inline bool
  empty() const
  {
    return _size == 0;
  }

  void
  push_back(const_reference elem)
  {
    if (_size == _capacity) {
      if (_capacity == 0) {
        _capacity = VECTOR_INIT_CAPACITY;
      } else {
        _capacity *= 2;
      }
      pointer old_data = _data;
      _data = static_cast<pointer>(malloc(sizeof(value_type) * _capacity));
      for (ptrdiff_t i = 0; i < _size; ++ i) {
        new (_data + i) value_type(std::move(old_data[i]));
        old_data[i].~value_type();
      }
      free(old_data);
    }

    new (_data + _size) value_type(elem);
    ++ _size;
  }

  value_type
  pop_back()
  {
    -- _size;
    auto result = _data[_size];
    _data[_size].~value_type();
    return result;
  }

  void
  resize(ptrdiff_t n, const_reference val)
  {
    if (n != _size || n != _capacity) {
      auto old_size = _size;
      pointer old_data = _data;
      _size = _capacity = n;
      _data = static_cast<pointer>(malloc(sizeof(value_type) * _capacity));
      for (ptrdiff_t i = 0; i < _size && i < old_size; ++ i) {
        new (_data + i) value_type(std::move(old_data[i]));
      }
      for (ptrdiff_t i = old_size; i < _size; ++ i) {
        new (_data + i) value_type(val);
      }

      for (ptrdiff_t i = 0; i < old_size; ++ i) {
        old_data[i].~value_type();
      }
      free(old_data);
    }
  }

  void
  resize(ptrdiff_t n)
  {
    resize(n, value_type());
  }

  iterator
  begin()
  {
    return _data;
  }

  iterator
  end()
  {
    return _data + _size;
  }

  const_iterator
  cbegin() const
  {
    return _data;
  }

  const_iterator
  cend() const
  {
    return _data + _size;
  }

  reverse_iterator
  rbegin()
  {
    return reverse_iterator(_data + _size - 1);
  }

  reverse_iterator
  rend()
  {
    return reverse_iterator(_data - 1);
  }

  const_reverse_iterator
  crbegin() const
  {
    return const_reverse_iterator(_data + _size - 1);
  }

  const_reverse_iterator
  crend() const
  {
    return const_reverse_iterator(_data - 1);
  }
};

// Tests

void check(bool value)
{
  if (!value) {
    std::cerr << "error" << std::endl;
    throw std::runtime_error("error");
  } else {
    std::cerr << ".";
  }
}

using Block = std::function<void ()>;

void
raises(const Block &block)
{
  bool raises = false;
  try {
    block();
  } catch(const std::runtime_error &) {
    raises = true;
  }
  check(raises);
}

// Check that destructor calls needed times
struct Counter {
private:
  static ptrdiff_t _links;
  int _value;
public:
  Counter(int _val) :
    _value(_val)
  {
    ++ _links;
  }

  Counter() :
    _value(0)
  {
    ++ _links;
  }

  ~Counter()
  {
    -- _links;
  }

  Counter(const Counter &other) :
    _value(other._value)
  {
    ++ _links;
  }

  Counter(Counter &&other) :
    _value(other._value)
  {
    ++ _links;
  }

  Counter &
  operator=(const Counter &) = default;
  Counter &
  operator=(Counter &&) = default;

  static ptrdiff_t
  links()
  {
    return _links;
  }

  bool
  operator==(const Counter &other) const
  {
    return _value == other._value;
  }
};

ptrdiff_t Counter::_links = 0;

void
test_init() {
  std::cerr << "test_init";

  Vector<Counter> a;
  check(a.size() == 0);
  check(a.empty());

  auto b = Vector<Counter>(3);
  check(b.size() == 3);
  check(!b.empty());

  b.clear();
  check(b.size() == 0);
  check(b.empty());

  Vector<Counter> c = {1, 2, 3};
  check(c[0] == 1);
  check(c[1] == 2);
  check(c[2] == 3);

  std::cerr << "OK" << std::endl;
}

void
test_indexing() {
  std::cerr << "test_indexing";

  auto a = Vector<Counter>(3);
  for (int i = 0; i < 3; ++ i) {
    a[i] = i;
  }

  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  std::cerr << "OK" << std::endl;
}

void
test_copy() {
  std::cerr << "test_copy";

  // Create new vector
  auto a = Vector<Counter>(3);
  for (int i = 0; i < 3; ++ i) {
    a[i] = i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  // Copy vector
  Vector<Counter> b(a);
  check(b.size() == 3);
  for (int i = 0; i < 3; ++ i) {
    check(b[i] == i);
  }

  // Change vector
  for (int i = 0; i < 3; ++ i) {
    b[i] = 3 + i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(b[i] == 3 + i);
  }

  // Original vector doesn't change
  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  Vector<Counter> c(10);

  // Copy vector
  c = a;
  check(c.size() == 3);
  for (int i = 0; i < 3; ++ i) {
    check(c[i] == i);
  }

  // Change vector
  for (int i = 0; i < 3; ++ i) {
    c[i] = 6 + i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(c[i] == 6 + i);
  }

  // Original vector doesn't change
  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  // Self copy
  a = a;
  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  std::cerr << "OK" << std::endl;
}

void
test_move() {
  std::cerr << "test_move";

  // Create new vector
  auto a = Vector<Counter>(3);
  for (int i = 0; i < 3; ++ i) {
    a[i] = i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  // Move vector
  Vector<Counter> b(std::move(a));
  check(b.size() == 3);
  for (int i = 0; i < 3; ++ i) {
    check(b[i] == i);
  }

  // Change vector
  for (int i = 0; i < 3; ++ i) {
    b[i] = 3 + i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(b[i] == 3 + i);
  }

  // Original vector is empty
  check(a.empty());
  check(a.size() == 0);

  Vector<Counter> c(10);

  // Move vector
  c = std::move(b);
  check(c.size() == 3);
  for (int i = 0; i < 3; ++ i) {
    check(c[i] == 3 + i);
  }

  // Change vector
  for (int i = 0; i < 3; ++ i) {
    c[i] = 6 + i;
  }
  for (int i = 0; i < 3; ++ i) {
    check(c[i] == 6 + i);
  }

  // Original vector is empty
  check(b.empty());
  check(b.size() == 0);

  std::cerr << "OK" << std::endl;
}

void
test_push_pop() {
  std::cerr << "test_push_pop";

  // Create new vector
  Vector<Counter> a = {0, 1, 2};
  for (int i = 0; i < 10; ++ i) { // Push elements
    a.push_back(i + 3);
    check(a[i + 3] == i + 3);
    check(static_cast<int>(a.size()) == i + 4);
  }
  for (int i = 12; i >= 0; -- i) { // Pop elements
    check(a.pop_back() == i);
    check(static_cast<int>(a.size()) == i);
  }
  check(a.empty()); // a is empty

  a.clear(); // Check after clear
  for (int i = 0; i < 10; ++ i) { // Push elements
    a.push_back(i);
    check(a[i] == i);
    check(static_cast<int>(a.size()) == i + 1);
  }
  for (int i = 9; i >= 0; -- i) { // Pop elements
    check(a.pop_back() == i);
    check(static_cast<int>(a.size()) == i);
  }
  check(a.empty()); // a is empty

  std::cerr << "OK" << std::endl;
}

void
test_resize() {
  std::cerr << "test_resize";

  // Create new vector
  Vector<Counter> a = {10};

  // Make size bigger
  a.resize(2);
  check(a.size() == 2);
  check(a[0] == 10);
  check(a[1] == 0);

  // Check with filler
  a.resize(3, 3);
  check(a.size() == 3);
  check(a[0] == 10);
  check(a[1] == 0);
  check(a[2] == 3);

  //Check with smaller size
  a.resize(1);
  check(a.size() == 1);
  check(a[0] == 10);

  std::cerr << "OK" << std::endl;
}

void
test_iterator() {
  std::cerr << "test_iterator";

  // Create new vector
  Vector<Counter> a(3) ;

  int i = 0;
  for (auto & e : a) {
    e = i;
    check(e == i);
    ++ i;
  }

  for (i = 0; i < 3; ++ i) {
    check(a[i] == i);
  }

  i = 0;
  for (const auto & e : a) {
    check(e == i);
    ++ i;
  }

  i = 0;
  for (auto it = a.rbegin(); it != a.rend(); ++ it) {
    *it = i;
    check(*it == i);
    ++ i;
  }

  for (i = 0; i < 3; ++ i) {
    check(a[i] == 2 - i);
  }

  i = 0;
  for (auto it = a.crbegin(); it != a.crend(); ++ it) {
    check(*it == i);
    ++ i;
  }

  std::cerr << "OK" << std::endl;
}

void
run_tests() {
  check(Counter::links() == 0);
  test_init();
  check(Counter::links() == 0);
  test_indexing();
  check(Counter::links() == 0);
  test_copy();
  check(Counter::links() == 0);
  test_move();
  check(Counter::links() == 0);
  test_push_pop();
  check(Counter::links() == 0);
  test_resize();
  check(Counter::links() == 0);
  test_iterator();
  check(Counter::links() == 0);
  std::cerr << std::endl;
}


int
main()
{
  try {
    run_tests();
  } catch(...) {
  }
}
