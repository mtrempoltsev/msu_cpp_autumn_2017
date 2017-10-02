#pragma once
#include <utility>

struct Token {
    enum Type {
        Operation,
        Number,
        End
    };
    Type type;
    int value;
};

int calc_parse(const char *str);
