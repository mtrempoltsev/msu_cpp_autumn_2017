#ifndef TABLEOFVARIABLES_H
#define TABLEOFVARIABLES_H
#include <vector>
#include "variable.h"
#include <iostream>
#include <typeinfo>

template<class T>
class TableOfVariables
{
public:
    TableOfVariables();
    Variable<T> getVariable(std::string& name);
    bool exist(std::string& name);
    void addVariable(Variable<T>&);
private:
    std::vector<Variable<T>> values;
};

template<class T>
TableOfVariables<T>::TableOfVariables()
    :values(){
    values.push_back(Variable<T>(std::string("Pi"), (T)3.14));
    values.push_back(Variable<T>(std::string("e"), (T)2.7));
}

template<class T>
Variable<T> TableOfVariables<T>::getVariable(std::string& name){
    for(int i = 0; i < values.size(); ++i){
        if(values[i].getName() == name){
            return values[i];
        }
    }
    //
    //std::cerr <<"syntax error: no such variable named " + name + "\n";
    throw std::bad_cast();
}

template<class T>
bool TableOfVariables<T>::exist(std::string& name){
    for(int i = 0; i < values.size(); ++i){
        if(values[i].getName() == name){
            return true;
        }
    }
    return false;
}

template<class T>
void TableOfVariables<T>::addVariable(Variable<T>& var){
    for(int i = 0; i < values.size(); ++i){
        if(values[i].getName() == var.getName()){
            //std::cerr <<"syntax error: variable exist\n";
            throw std::bad_cast();
            //return values[i];
        }
    }
    values.push_back(var);
}
#endif // TABLEOFVARIABLES_H
