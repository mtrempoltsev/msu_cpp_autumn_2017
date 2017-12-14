# include "vector.h"
#include <iostream>

//Практическая работа
//
//Написать свой контейнер Vector аналогичный std::vector и итератор для него.
//Из поддерживаемых методов достаточно
//operator[]  # Get element
//push_back   # Put at the end
//pop_back    # Pop last element
//empty       # Is vector empty?
//size        # Size
//clear       # Clear
//begin       # Iterator start
//end         # Iterator end
//rbegin      # Begin pointer
//rend        # End pointer
//resize      # Resize

int main()
{
    try{
        Vector<int> V(10);
        std :: cout << "Testing\n";

        std :: cout << "Is V empty\n>>" << V.empty() << "\n";
        std :: cout << "Vector<int> V(10)\n";
        std :: cout << "Size     \n>> " << V.size() << "\n";
        
        std :: cout << "Capacity \n>> " << V.__capacity() << "\n";
        
        std :: cout << "V <- range(10)\n";
        
        for(int i = 0; i<V.size(); i++)
            V[i] = i;
        
        std :: cout << "print V in iteraton\n>> ";
        for(int i: V)
            std :: cout << i << " ";

        std :: cout << "\nprint V in reverse iteraton\n>> ";
        for(Vector<int>::Riterator RIt = V.rbegin();RIt != V.rend();++RIt)
            std :: cout << *RIt << " ";
        
        std :: cout << "\nresize(3,1); V[0] = -1\n";
        V.resize(3, 1);
        V[0] = -1;
        
        std :: cout << "print V\n>> ";
        V.print();

        std :: cout << "\nV.pop_back()\n";

        std :: cout << ">> " << V.pop_back();
        std :: cout << "\nV.clear()\n";
//        V.clear();
//        for(int i=0; i<20; i++)
//            V.push_back(i);
//        V.print();
        V.clear();
    }
    catch(const char* c) {
        cout << "\n" << c << "\n";
        return 1;
    }
    return 0;
}

