#include <iostream>
#include "vec.hpp"

int main(int argc, char** argv)
{
    Vector<int> vec(1);
    vec[0] = 5;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    for(int i = 0; i < 8; i ++)
    {
        vec.push_back(i+1);
    }

    std::cout << "Test create:" ;
    {
        Vector<int> vec(3);
        vec[0] = 1;
        vec[1] = 2;
        vec[2] = 3;

        if (vec[0] == 1 && vec[1] == 2 && vec[2] == 3)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    std::cout << "Test create by initializer_list:" << std::endl;
    {
        Vector<int> vec = {1,2,3};

        if (vec[0] == 1 && vec[1] == 2 && vec[2] == 3)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    std::cout << "Test resize:" << std::endl;
    {
        Vector<int> vec = {1,2,3,4,5};

        vec.resize(3);

        if (vec[0] == 1 && vec[1] == 2 && vec[2] == 3 && vec.size() == 3)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    std::cout << "Test push:" << std::endl;
    {   
        Vector<int> vec(0);
        for(int i = 0; i < 50; ++i)
        {
            vec.push_back(i+1);
        }

        bool isok = true;

        for(int i = 0; i < 50; ++i)
        {
            if(vec[i] != i+1)
            {
                isok = false;
            }
        }

        if(isok && vec.size() == 50)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    std::cout << "Test iterator:" << std::endl;
    {   
        Vector<int> vec = {1,2,3,4,5};
        bool isok = true;
        int i = 1;
        for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (*it != i)
            {
                isok = false;
            }
            ++i;
        }
        if(isok)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    
    std::cout << "Test reverse_iterator:" << std::endl;
    {
        Vector<int> vec = {1,2,3,4,5};
        bool isok = true;
        int i = 5;
        for (Vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
        {
            if (*it != i)
            {
                isok = false;
            }
            --i;
        }
        if(isok)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }
    

    std::cout << "Test pop:" << std::endl;
    {
        Vector<int> vec = {1,2,3,4,5};
        vec.pop_back();
        if(vec[0] == 1 && vec[1] == 2 && vec[2] == 3 && vec[3] == 4 && vec.size() == 4)
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }

    std::cout << "Test clear:" << std::endl;
    {
        Vector<int> vec = {1,2,3,4,5};
        vec.clear();
        if(vec.empty())
        {
            std::cout << "pass" << std::endl;
        }
        else 
        {
            std::cout << "not pass" << std::endl;
        }
    }
    
    return 0;
}