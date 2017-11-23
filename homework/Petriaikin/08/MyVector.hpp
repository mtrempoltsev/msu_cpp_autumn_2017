#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

//==================================================================================================

#include "MyVector.h"

//==================================================================================================

template<typename T>
MyVector<T>::MyVector(size_t size) : current_elements_(size), capacity_(size), array_(std::make_unique<T[]>(size))
{}

template<typename T>
MyVector<T>::MyVector(size_t size, const T& value) : current_elements_(size), capacity_(size), array_(std::make_unique<T[]>(size))
{
	for (size_t i = 0; i < size; i++)
	{
		array_[i] = value;
	}
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> elements) : MyVector(elements.size())
{
	int i = 0;
	for (auto current = elements.begin(); current != elements.end(); ++current)
	{
		array_[i] = *current;
		i++;
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& vector)
{
	capacity_ = vector.capacity_;

	array_ = std::make_unique<T[]>(capacity_);
	current_elements_ = vector.size();

	for (size_t i = 0; i < current_elements_; i++)
	{
		array_[i] = vector[i];
	}
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& vector)
{
	capacity_ = vector.capacity_;
	current_elements_ = vector.size();

	array_ = vector.array_;
}

//==================================================================================================

template<typename T>
typename MyVector<T>::reference MyVector<T>::At_ (int position) const
{
	CheckIndex_(position);
	return array_[position];
}

template<typename T>
typename MyVector<T>::const_reference MyVector<T>::operator[] (int position) const
{
	return At_(position);
}

template<typename T>
typename MyVector<T>::reference MyVector<T>::operator[] (int position)
{
	return At_(position);
}

//==================================================================================================

template<typename T>
void MyVector<T>::push_back(const T& element)
{
	if (current_elements_ == capacity_) { resize((size_t) capacity_*resize_coefficient_+1); }
	array_[current_elements_++] = element;
}

template<typename T>
void MyVector<T>::pop_back()
{
	--current_elements_;
}

template<typename T>
void MyVector<T>::resize(size_t new_size)
{
	if (new_size == capacity_) { return; }
	std::unique_ptr<T[]> new_array = std::make_unique<T[]>(new_size);

	size_t count_for_copy = (current_elements_ > new_size) ? new_size : current_elements_;
	for (size_t i = 0; i < count_for_copy; i++)
	{
		new_array[i] = std::move(array_[i]);
	}

	array_ = std::move(new_array);
	capacity_ = new_size;
	current_elements_ = count_for_copy;
}

template<typename T>
void MyVector<T>::clear()
{
	current_elements_ = 0;
}

//==================================================================================================

template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() const
{
	return CreateIterator_(const_cast<MyVector<T>&>(*this), 0);
}

template<typename T>
typename MyVector<T>::reverse_iterator MyVector<T>::rbegin() const
{
	if (current_elements_ == 0) { return rend(); }
	return CreateReverseIterator_(const_cast<MyVector<T>&>(*this), current_elements_-1);
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() const
{
	return CreateIterator_(const_cast<MyVector<T>&>(*this), current_elements_);
}

template<typename T>
typename MyVector<T>::reverse_iterator MyVector<T>::rend() const
{
	return CreateReverseIterator_(const_cast<MyVector<T>&>(*this), -1);
}


//==================================================================================================

#endif