#include <algorithm>
#include <iostream>
#include <vector>

template <class Container>
class BackInserterImpl
    : public std::iterator
        <
            std::forward_iterator_tag,
            typename Container::value_type
        >
{
    Container& cont_;
public:
    using ValueType = typename Container::value_type;

    explicit BackInserterImpl(Container& c)
        : cont_(c)
    {
    }

    void operator++()
    {
        // nothing to do
    }

    ValueType& operator*()
    {
        cont_.push_back(ValueType());
        return cont_.back();
    }
};

template <class Container>
BackInserterImpl<Container> BackInserter(Container& c)
{
    return BackInserterImpl<Container>(c);
}

int main()
{
    std::vector<int> v;
    int data[] = { 1, 2, 3 };
    const auto size = 
        sizeof(data) / sizeof(data[0]);
    std::copy(data, data + size, BackInserter(v));
    std::for_each(v.begin(), v.end(), [](int x) { std::cout << x; });
    return 0;
}

