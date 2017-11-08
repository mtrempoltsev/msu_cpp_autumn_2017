#pragma
#include <iostream>
#include <limits>
using namespace std;


template <typename T>
class Parser
{
};

template <>
class Parser<double>
{
public:
   static bool isParsable (char c)
   {
      if ((c>='0') && (c<='9') || (c=='.'))
      {
         return true;
      }
      return false;
   }

   static double parse(const char*& str)
   {
      size_t size = 0;
      double value = std::stod(str, &size);
      str += size;
      return value;
   }
};


template <>
class Parser<long>
{
public:
   static bool isParsable (char c)
   {
      if ((c>='0') && (c<='9'))
      {
         return true;
      }
      return false;
   }

   static long parse(const char*& str)
   {
      size_t size = 0;
      double value = std::stod(str, &size);
      str += size;
      return value;
   }
};




template <>
class Parser<int>
{
public:
   static bool isParsable (char c)
   {
      return Parser<long>::isParsable(c);
   }

   static int parse(const char*& str)
   {
      long value = Parser<long>::parse(str);
      if ( (value > std::numeric_limits<int>::max()) || (value < std::numeric_limits<int>::min()))
      {
         cout << "Out of bounds" << endl;
      }
      return value;
   }
};
