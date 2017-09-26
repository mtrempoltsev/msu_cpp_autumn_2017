#include <chrono>
#include <iostream>
#include "header.h"
#define NUMBER_OF_TESTS 10


int main(int argc, char* argv[])
{
   for(int i = 0; i < NUMBER_OF_TESTS; i++){
       if(argc > 1) {
           switch(*argv[1]) {
               case 'r': {
                   std::cout << "Time of calculating by rows: ";
                   by_rows();
                   break;
               }
               case 'c': {
                   std::cout << "Time of calculating by columns: ";
                   by_columns();
                   break;
               }
               default:{
                   std::cout << "Time of calculating by rows: ";
                   by_rows();
                   std::cout << "Time of calculating by columns: ";
                   by_columns();
                   break;
               }
           }
       }else{
           std::cout << "Time of calculating by rows: ";
           by_rows();
           std::cout << "Time of calculating by columns: ";
           by_columns();
       }
   }

}
