#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>

template<class T>
class Variable
{
public:
    Variable(const std::string&, T);
    std::string getName() const;
    T getValue() const;
    void setValue(T);
private:
    std::string name;
    T value;
};

template<class T>
Variable<T>::Variable(const std::string& name, T val)
    :name(name), value(val)
{

}

template<class T>
T Variable<T>::getValue() const
{
    return value;
}

template<class T>
std::string Variable<T>::getName() const
{
    return name;
}

template<class T>
void Variable<T>::setValue(T val){
    value = val;
}
#endif // VARIABLE_H
