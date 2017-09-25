#include <chrono>
#include <iostream>
#include "by_rows.h"
#include "by_columns.h"
#define NUMBER_OF_TESTS 10

//using namespace std;

int main(int argc, char* argv[])
{
    int avg_by_rows = 0;
    int avg_by_columns = 0;
    std::cout << *argv[1] << std::endl;
   for(int i = 0; i < NUMBER_OF_TESTS; i++){
       if(argc > 1) {
           switch(*argv[1]) {
               case 'r': {
                   std::cout << "by_rows: ";
                   by_rows();
               }
               case 'c': {
                   std::cout << "by_columns: ";
                   by_columns();
               }
               default:{}
           }
       }
   }

}