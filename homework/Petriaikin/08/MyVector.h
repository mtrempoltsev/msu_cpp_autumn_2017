#ifndef MYVECTOR_H
#define MYVECTOR_H

//==================================================================================================

#include <memory>
#include <exception>

//==================================================================================================

template<typename T>
class MyVector
{
	//Система итераторов
	private:
		class iterator_base : public std::iterator<std::random_access_iterator_tag, T>
		{
			protected:
				MyVector<T>& vector_object_;
				size_t current_position_;

			public:
				typedef T& reference;

				//Конструктор копирования и оператор присваивания по умолчанию: класс ресурсами не управляет. Аналогично у наследников
				//const_iterator_base(const const_iterator_base&) = default;
				//const_iterator_base& operator=(const const_iterator_base&) = default;

				iterator_base(MyVector<T>& vector_object, size_t current_position) : vector_object_(vector_object), current_position_(current_position)
				{}

				bool operator==(const iterator_base& it) const
				{
					//Могут сравниваться только итераторы одного вектора
					if (&vector_object_ != &it.vector_object_) { return false; }
					return current_position_ == it.current_position_;
				}
				bool operator!=(const iterator_base& it) const
				{
					return !(it == *this);
				}

				reference operator*() const
				{
					//.end() недопустимо разыменовывать и .rend() тоже
					if (current_position_ == vector_object_.size() || current_position_ == -1) { throw std::out_of_range("*end() or *rend()"); }
					return vector_object_[current_position_];
				}

			//Функции сдвига. Специализируются в производных классах
			protected:
				virtual void CheckShift_(int shift)
				{
					vector_object_.CheckIndex_(current_position_ + shift);
				}

				iterator_base& operator++()
				{
					return (*this += 1);
				}
				iterator_base& operator--()
				{
					return (*this -= 1);
				}
				iterator_base& operator+=(int shift)
				{
					CheckShift_(shift);
					current_position_ += shift;
					return *this;
				}
				iterator_base& operator-=(int shift)
				{
					return (*this += -shift);
				}

				//Реализация зависит от наследника
				template<typename U>
				U IncrementPostfix_()
				{
					U tmp_object(*this);
					U::operator++();
					return tmp_object;
				}
				template<typename U>
				U DecrementPostfix_()
				{
					U tmp_object(*this);
					U::operator--();
					return tmp_object;
				}
				template<typename U>
				U OperatorPlus_(int shift)
				{
					return (U(*this) += shift);
				}
				template<typename U>
				U OperatorMinus_(int shift)
				{
					return (U(*this) -= shift);
				}
		};

	public:
		class iterator : public iterator_base
		{
			protected:
				void CheckShift_(int shift) override
				{
					if (this->current_position_ + shift == this->vector_object_.size()) { return; } //Прямой итератор может указывать на элемент за последним
					iterator_base::CheckShift_(shift);
				}

			private:
				//Итераторы могут создаваться только самим вектором
				iterator(MyVector<T>& vector_object, size_t current_position) : iterator_base(vector_object, current_position)
				{
					CheckShift_(0);
				}
				friend iterator MyVector<T>::CreateIterator_(MyVector<T>&, int);

			public:
				iterator& operator++() { return static_cast<iterator&>(iterator_base::operator++());  }
				iterator& operator--() { return static_cast<iterator&>(iterator_base::operator--());  }
				iterator& operator+=(int shift) { return static_cast<iterator&>(iterator_base::operator+=(shift)); }
				iterator& operator-=(int shift)	{ return static_cast<iterator&>(iterator_base::operator-=(shift)); }

				iterator operator++(int) { return iterator_base::IncrementPostfix_(); }
				iterator operator--(int) { return iterator_base::DecrementPostfix_(); }
				iterator operator+(int shift) { return iterator_base::OperatorPlus_(shift);  }
				iterator operator-(int shift) { return iterator_base::OperatorMinus_(shift); }
		};

		class reverse_iterator : public iterator_base
		{
			protected:
				void CheckShift_(int shift) override
				{
					if (this->current_position_ + shift == -1) { return; } //Обратный итератор может иметь позицию -1 (rend)
					iterator_base::CheckShift_(shift);
				}

			private:
				//Итераторы могут создаваться только самим вектором
				reverse_iterator(MyVector<T>& vector_object, size_t current_position) : iterator_base(vector_object, current_position)
				{
					CheckShift_(0);
				}
				friend reverse_iterator MyVector<T>::CreateReverseIterator_(MyVector<T>&, int);

			public:
				reverse_iterator& operator++() { return static_cast<reverse_iterator&>(iterator_base::operator--()); }
				reverse_iterator& operator--() { return static_cast<reverse_iterator&>(iterator_base::operator++()); }
				reverse_iterator& operator+=(int shift) { return static_cast<reverse_iterator&>(iterator_base::operator-=(shift)); }
				reverse_iterator& operator-=(int shift) { return static_cast<reverse_iterator&>(iterator_base::operator+=(shift)); }

				reverse_iterator operator++(int) { return iterator_base::DecrementPostfix_(); }
				reverse_iterator operator--(int) { return iterator_base::IncrementPostfix_(); }
				reverse_iterator operator+(int shift) { return iterator_base::OperatorMinus_(shift); }
				reverse_iterator operator-(int shift) { return iterator_base::OperatorPlus_(shift);  }
		};

	//--------------------------------------------------------------------------------------------------

	private:
		const float resize_coefficient_ = 1.5;

		std::unique_ptr<T[]> array_;
		size_t current_elements_;
		size_t capacity_;

	private:
		void CheckIndex_(size_t index) const
		{
			if (index >= current_elements_ || index < 0) { throw std::out_of_range("CheckIndex_() of MyVector"); }
		}

		T& At_(int postion) const;

		static iterator CreateIterator_(MyVector<T>& vector_object, int position) { return iterator(vector_object, position); }
		static reverse_iterator CreateReverseIterator_(MyVector<T>& vector_object, int position) { return reverse_iterator(vector_object, position); }

	public:
		typedef const T& const_reference;
		typedef T& reference;

		MyVector(std::initializer_list<T> elements);
		MyVector(size_t size);
		MyVector(size_t size, const T& value);

		MyVector(const MyVector<T>& vector);
		MyVector(MyVector<T>&& vector);

		~MyVector() = default; //потому что используем unique_ptr

		const_reference operator[] (int position) const;
		reference operator[] (int position);

		size_t size() const { return current_elements_; }
		bool empty() const { return current_elements_ != 0; }

		void push_back(const T& element);
		void pop_back(); //Не гарантирует удаления объекта (если он лежит по значению)

		void resize(size_t new_size); //Обрезает массив, если new_size < current_elements

		void clear(); //Не гарантирует удаления объекта (если он лежит по значению). Capacity не изменяется. Resize(0) - делает удаление массива

		iterator begin() const;
		iterator end() const;
		reverse_iterator rbegin() const;
		reverse_iterator rend() const;
};

//==================================================================================================

#endif