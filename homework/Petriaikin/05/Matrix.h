#pragma once
#ifndef MATRIX_H
#define MATRIX_H

//========================================================================

#include <vector>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <memory.h>

//========================================================================

//#define DEBUG(x) std::cout << x << std::endl;
#define DEBUG(x)

//========================================================================

namespace Constants
{
	const double epsiol = 1e-9;
}

template<typename T>
T Abs(T arg);

//========================================================================

template<typename T>
class Matrix
{
	private:
		class MatrixRow //Объявляем приватным, чтобы его объекты не могли создавать вне Matrix
		{
			private:
				T* row_;
				size_t max_column_;

			public:
				MatrixRow(T* row, size_t max_columns);

				T& operator[] (size_t column);
				const T& operator[] (size_t column) const;

				//Операции с рядами поддерживать не будем
		};

	private:
		//Можно было бы использовать vector, но тогда бы задание теряло смысл (прокси-класс не нужен)
		//Кроме того, здесь мы тренируемся управлять памятью
		T* matrix_; 

		//Форма матрицы
		std::pair<size_t, size_t> shape_;

		void CreateAndCopy_(size_t size, const T* data);
		void FreeMatrix_();
		void AllocateMatrix_(size_t size);

		//Счетчик выделений памяти
		static int memory_allocated_;

	public:
		Matrix(std::pair<size_t, size_t> shape, const std::vector<T>& data);

		//Превращать вектор в матрицу неявно - разумное преобразование.
		//Вектор будет считаться столбцом: на строку можно умножить только столбец.
		Matrix(const std::vector<T>& data);
		Matrix(std::pair<size_t, size_t> shape, T fill_value = 0);
		Matrix(const Matrix<T>& matrix);
		Matrix(Matrix<T>&& matrix);

		//Для совместимости с boost
		Matrix(size_t rows, size_t columns, T fill_value = 0);

		Matrix<T>& operator= (const Matrix<T>& arg);
		Matrix<T>& operator= (Matrix<T>&& arg);

		//Операторы, возвращающие временные объекты
		Matrix<T> operator+ (const Matrix<T>& arg) const;
		Matrix<T> operator- () const;
		Matrix<T> operator- (const Matrix<T>& arg) const;
		Matrix<T> operator* (const Matrix<T>& arg) const;
		Matrix<T> operator* (T arg) const;

		//Операторы, возвращающие измененный объект
		Matrix<T>& operator+= (const Matrix<T>& arg);
		Matrix<T>& operator-= (const Matrix<T>& arg);
		Matrix<T>& operator*= (const Matrix<T>& arg);
		Matrix<T>& operator*= (T arg);

		bool operator== (const Matrix<T>& arg) const;
		bool operator!= (const Matrix<T>& arg) const;

		MatrixRow operator[] (size_t row);
		const MatrixRow operator[] (size_t row) const;

		//Деструктор, который может быть "болтливым"
		~Matrix();

		size_t Rows()    const { return shape_.first;  }
		size_t Columns() const { return shape_.second; }

		static int GetMemoryAllocated() { return memory_allocated_; }
};

//========================================================================

#endif