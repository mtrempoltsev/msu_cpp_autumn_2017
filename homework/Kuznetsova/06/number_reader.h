#pragma once
#include <limits>
//#include <iostream>
template <typename T> class NumericTraits {};

template <> class NumericTraits<int> {
  public:
    static constexpr int min = std::numeric_limits<int>::lowest();
    static constexpr int max = std::numeric_limits<int>::max();
};
template <> class NumericTraits<long int> {
  public:
    static constexpr long int min = std::numeric_limits<long int>::lowest();
    static constexpr long int max = std::numeric_limits<long int>::max();
};
template <typename T> class NumberReader {};
template <> class NumberReader<int> {
  public:
    static bool read_number(char *&text, int &value) {
        long long int tmp = 0;
        for (auto c = *text; c >= '0' && c <= '9';) {
            // std::cout << c << std::endl;
            tmp = tmp * 10 + c - '0';
            c = *++text;
        }

        if (tmp < NumericTraits<int>::min || tmp > NumericTraits<int>::max) {
            return false;
        }
        value = tmp;
        return true;
    }
};
//long int limits are checked through long long int so correctness is not guaranteed
template <> class NumberReader<long int> {
  public:
    static bool read_number(char *&text, long int &value) {
        long long int tmp = 0;
        for (auto c = *text; c >= '0' && c <= '9';) {
            tmp = tmp * 10 + c - '0';
            c = *++text;
        }
        if (tmp < NumericTraits<long int>::min ||
            tmp > NumericTraits<long int>::max) {
        
            return false;
        }
        value = tmp;
        return true;
    }
};
template <> class NumberReader<double> {
  public:
    static bool read_number(char *&text, double &value) {
        double whole_tmp = 0;
        for (auto c = *text; c >= '0' && c <= '9';) {
            whole_tmp = whole_tmp * 10 + c - '0';
            c = *++text;
        }
        if (*text == '.') {
            double fraction_tmp = 0;
            double i = 0.1;
            for (auto c = *++text; c >= '0' && c <= '9';) {
                fraction_tmp += (c - '0') * i;
                i /= 10;
                c = *++text;
            }
            value = fraction_tmp + whole_tmp;
            return true;
        }

        else {
            value = whole_tmp;
            return true;
        }
        return false;
    }
};
