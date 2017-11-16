#include <limits>

template <typename T>
struct NumericTraits
{
	static constexpr T min = std::numeric_limits<T>::lowest();
	static constexpr T max = std::numeric_limits<T>::max();
};

