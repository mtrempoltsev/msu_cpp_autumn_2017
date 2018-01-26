#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <algorithm> // fill, move(ii..ii -> oi), min
#include <iterator>  // distance, reverse_iterator
#include <vector>    // for testing
#include <utility>   // std::move(o)

template<typename T>
class Vector {
	std::unique_ptr<T[]> data;
	size_t siz, capacity;

	// решаем, нужно ли увеличивать/уменьшать массив
	// делаем это с шагом 3/2
	// обновляем size и capacity чтобы отражать изменения
	// гарантирует то, что есть место как минимум для want объектов
	void ensure(size_t want) {
		static const int cap_num = 3, cap_den = 2;
		if (want > capacity && want < capacity * cap_num / cap_den) {
			// выделяем как минимум 3/2 от текущей емкости, чтобы сохранить линейную сложность
			capacity = capacity * cap_num / cap_den;
		} else if (want <= capacity && want > capacity * cap_den / cap_num) {
			// не беспокоиться если нужно сократить, но требуемый размер > 2/3 емкости
			siz = want;
			return;
		} else {
			// если запрошенный размер сильно отличается от текущего, то просто выделяем столько, сколько просят
			capacity = want;
		}
		
		T* new_data = new T[capacity]; 
		
		// перемещаем то, что нужно
		// std::move используется, чтобы определить может ли объект t быть "перемещен"
		std::move(data.get(), data.get() + std::min(siz, want), new_data);
		// освобождаем после std::move
		data.reset(new_data); 
		siz = want;
	}

public:
	typedef T *iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	Vector(size_t size = 0, const T& init = T()) : siz(0), capacity(0) {
		
		ensure(size);
		if (size) // нужно заполнить полученное пространство чем-то конкретным
			std::fill_n(data.get(), siz, init);
	}

	// InputIterator
	// cppreference : один из конструкторов должен принимать именно их
	template<typename II>
	Vector(II first, II last) : siz(0), capacity(0) {
		
		ensure(std::distance(first, last));
		// Копирует элементы диапазона [first, last) в диапазон, начинающийся с d_first. 
		std::copy(first, last, data.get());
	}

	Vector& operator=(const Vector & other) {
		
		ensure(other.siz);
		// Если count > 0, копирует ровно count значений из диапазона, начинающегося с first в диапазон, начинающийся с result. 
		std::copy_n(other.data.get(), other.siz, data.get());
		
		return *this;
	}

	Vector (const Vector & other) : siz(0), capacity(0) {
		
		*this = other;
	}

	Vector& operator=(Vector && other) {
		
		siz = other.siz;
		capacity = other.capacity;
		// деструктор очистит
		std::swap(data, other.data);
		
		return *this;
	}

	Vector(Vector && other) : siz(0), capacity(0) {
		
		*this = std::move(other);
	}

	T& operator[](size_t i) {
		// cppreference: проверка границ не выполняется.
		return data[i];
	}

	void push_back(const T& val) {
		// увеличение размера на 1
		ensure(siz+1); 
		// siz-1 это индекс последнего элемента
		data[siz-1] = val; 
	}

	void pop_back() {
		
		ensure(siz-1);
	}

	bool empty() const {
		
		return !siz;
	}

	size_t size() const {
		
		return siz;
	}

	void clear() {
		
		ensure(0);
	}

	iterator begin() {
		
		return data.get();
	}

	iterator end() {
		
		return data.get() + siz;
	}

	// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	reverse_iterator rbegin() {
		
		return reverse_iterator(data.get() + siz);
	}
	
	// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
	reverse_iterator rend() {
		
		return reverse_iterator(data.get());
	}

	void resize(size_t new_size, const T& val = T()) {
		
		size_t old_size = siz;
		ensure(new_size);
		
		if (new_size > old_size)
			// Присваивает заданное значение value всем элементам диапазона [first, last).
			std::fill(data.get() + old_size, data.get() + new_size, val);
	}
};

int main() 
{
	Vector<int> v((size_t)55, 999);
	
	assert(v.size() == 55);
	assert(v[54] == 999);
	
	{
		std::vector<int> w {1, 2, 3, 4, 5};
		Vector<int> x{w.begin(), w.end()};
		
		assert(x.size() == w.size());
		
		for (size_t i = 0; i < w.size(); i++)
			assert(x[i] == w[i]);

		Vector<int> y{x};
		
		assert(y.size() == x.size());
		
		for (size_t i = 0; i < x.size(); i++)
			assert(y[i] == x[i]);

		v = std::move(y);
	}

	assert(v.size() == 5);

	v.push_back(10);
	assert(v[v.size()-1] == 10);
	
	v.pop_back();
	assert(v.size() == 5);
	
	v.clear();
	assert(v.size() == 0);

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	v.resize(10, -1);

	std::vector<int> w{v.begin(), v.end()};
	
	auto vit = v.rbegin();
	auto wit = w.rbegin();

	while (wit != w.rend()) {
		assert(*vit == *wit);
		wit++;
		vit++;
	}

	assert(vit == v.rend());

	return 0;
}
