#pragma once
#include <vector>
#include <string>

template <typename T>
class Slice {
public:
    T& operator[](size_t i) {
        if (i >= size) {
            throw std::runtime_error(std::string("[Slice]: invalid index: ") + std::to_string(i));
        }
        return contentSlice[i];
    }

    T& operator[](size_t i) const {
        if (i >= size) {
            throw std::runtime_error(std::string("[Slice]: invalid index: ") + std::to_string(i));
        }
        return contentSlice[i];
    }

    Slice(T* slice, size_t size) : contentSlice(slice), size(size) {
    }

    Slice() = delete;
private:
    T* contentSlice;

    const size_t size;
};