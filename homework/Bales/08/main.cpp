#include "TVector.h"

void check(bool predic, int numLine = -1)
{
    if (!predic)
    {
        std::cerr << "Error is occured![:" << numLine << "]\n";
    }
}

void CheckInit()
{
    std::cout << "CheckInit is started!\n";    
    TVector<double> vec1 = { 1.3, 2.3, 3.3, 4.3, 5.3 };
    TVector<double> vec2;
    TVector<double> vec3(5);
    TVector<double> vec4(5, 1.5);
    check(vec1[0] == 1.3 && vec1[1] == 2.3 
        && vec1[2] == 3.3 && vec1[3] == 4.3 
        && vec1[4] == 5.3, __LINE__);
    check(vec2.size() == 0 && vec2.data() == nullptr, __LINE__);
    check(vec3.size() == 5 && vec3.data() != nullptr, __LINE__);
    check(vec4[0] == 1.5 && vec4[1] == 1.5 
        && vec4[2] == 1.5 && vec4[3] == 1.5 
        && vec4[4] == 1.5, __LINE__);
    std::cout << "CheckInit is ended!\n";            
}

void CheckPushAndPopBack()
{
    std::cout << "CheckPushAndPopBack is started!\n";
    TVector<int> vec;
    for (int i = 0; i < 32; ++i) 
    {
        vec.push_back(i);
    }
    check(vec.size() == 32, __LINE__);
    for (int i = 0; i < 32; ++i) 
    {
        check(vec[i] == i, __LINE__);
    }
    while (!vec.empty()) 
    {
        vec.pop_back();
    }
    check(vec.size() == 0 && vec.data() == nullptr, __LINE__);
    std::cout << "CheckPushAndPopBack is ended!\n";
}

void CheckIterators()
{
    std::cout << "CheckIterators is started!\n";
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int> crVec;
    for (auto iter = vec.crbegin(); iter != vec.crend(); ++iter)
    {
        crVec.push_back(*iter);
    }
    check(crVec.size() == 5);
    for (int i = 5; i >= 1; --i)
    {
        check(crVec[4 - (i - 1)] == i, __LINE__);
    }
    TVector<int> cVec;
    for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter)
    {
        cVec.push_back(*iter);
    }    
    check(cVec.size() == 5, __LINE__);
    for (int i = 0; i < 5; ++i)
    {
        check(cVec[i] == i + 1, __LINE__);
    }    
    std::cout << "CheckIterators is ended!\n";
}

int main(int argc, char* argv[]) {
    CheckInit();
    CheckPushAndPopBack();
    CheckIterators();
    return 0;
}