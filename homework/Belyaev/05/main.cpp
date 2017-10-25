#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;
template <class T>
class row{
public:
    row<T>(size_t elem, T* ptr):
            elem(elem),v(ptr){}
    ~row<T>() {}
    T& operator[](const size_t pos){
        if(pos >= elem){
            assert(!"index out of range");;
        }
        return v[pos];
    }
private:
    size_t elem;
    T *v;

};
template <class T>
class matrix{
public:
    matrix<T>(size_t rows, size_t cols):
            rows(rows),cols(cols)
    {
        if((cols < 1)||(rows < 1))
            assert(!"index out of range");
        a = new T[rows*cols];
        memset(a, 0, sizeof(T) * rows * cols);
    }

    ~matrix<T>(){
        delete[] a;
    }
    matrix<T>(const matrix<T>& copied)
            : rows(copied.rows)
            , cols(copied.cols)
    {
        a = new T[rows*cols];
        std::copy(copied.a, copied.a + rows * cols, a);
    }
    matrix<T>& operator=(const matrix<T>& copied)
    {
        if (this == &copied)
            return *this;
        if((this->cols != copied.cols) || (this->rows != copied.rows)){
            delete[] a;
            a = new T[copied.rows * copied.cols];
        }
        rows = copied.rows;
        cols = copied.cols;
        std::copy(copied.a, copied.a + rows * cols, a);
        return *this;
    }

    matrix<T>(matrix<T>&& movied)
    : rows(std::move(movied.rows))
    , cols(std::move(movied.cols))
    {
        a = movied.a;
        movied.a = nullptr;
    }

    matrix<T>& operator=(matrix<T>&& movied)
    {
        if (this == &movied)
            return *this;
        delete[] a;
        rows = movied.rows;
        cols = movied.cols;
        a = movied.a;
        movied.a = nullptr;
        return *this;
    }

    bool nullptrCheck() const{
        return(this->a == nullptr);
    }

    int getRows(){
        return this->rows;
    }

    int getColumns(){
        return this->cols;
    }

    row<T> operator[](const size_t val) const{
        if(val >= (*this).rows)
            assert(!"index out of range");
        return row<T>(cols, a+val*cols);
    }

    matrix<T>& operator*=(const int rval){
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                (*this)[i][j] *= rval;
            }
        }
        return *this;
    }

    matrix<T>& operator*(const int rval) const{
        matrix<T> res(rows, cols);
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                res[i][j] = (*this)[i][j] * rval;
            }
        }
        return res;
    }

    matrix<T>& operator*=(const vector<T> &rval){
        if(cols != rval.size()){
            assert(!"index out of range");
        }
        matrix<T>* res = new matrix<T>(rows,1);
        for(size_t i = 0; i < rows; i++){
			(*res)[i][0] = 0;
            for(size_t j = 0; j < cols; j++){
                (*res)[i][0] += (*this)[i][j] * rval[j];
            }
        }
        delete[] this->a;
        this->a = res->a;
        this->cols = res->cols;
        this->rows = res->rows;
        res->a = nullptr;
        delete res;
        return *this;
    }

    vector<T> operator*(vector<T> &rval) const{
        if(cols != rval.size()){
            assert(!"index out of range");
        }
        vector<T> res(rows);
        //vector<T>* res = new vector<T>(rows);
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                res[i] += (*this)[i][j] * rval[j];
            }
        }
        return res;
    }


    bool operator==(const matrix<T> &rval) const{
        if((cols != rval.cols)||(rows != rval.rows)){
            assert(!"index out of range");
        }
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                if((*this)[i][j] != rval[i][j])
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const matrix<T> &rval) const{
        return !(*this == rval);
    }

private:
    size_t rows;
    size_t cols;
    T *a;
};

void check(bool value)
{
    if (!value)
        cout << "error" << endl;
}

int main() {
    matrix<double> t1(2, 2);

    t1[0][0] = 1.0;
    t1[0][1] = 2.0;
    t1[1][0] = 3.0;
    t1[1][1] = 4.0;

    matrix<double> t2(2, 2);
    t2[0][0] = 1.0;
    t2[0][1] = 2.0;
    t2[1][0] = 3.0;
    t2[1][1] = 4.0;

    matrix<double> t3(2, 2);
    t3[0][0] = 1;
    t3[0][1] = 2;
    t3[1][0] = 2;
    t3[1][1] = 4;

    matrix<double> t4(2, 2);
    t4[0][0] = 5;
    t4[0][1] = 10;
    t4[1][0] = 15;
    t4[1][1] = 20;

    check(t1[0][0] == 1); //Checking element acquisition ([])
    check(t1 == t2); //Checking comparision (==)
    check(t1 != t3); //Checking comparision (!=)

    matrix<double> t5(15, 10);
    check(t5.getRows() == 15); //Checking rows acquisition
    check(t5.getColumns() == 10); //Checking columns acquisition

    vector<double> vec1 = {-1, 1};
    vector<double> vec2(2);
    vector<double> vec3 = {1, 1};
    matrix<double> vec4(2,1);
    vec4[0][0] = 1;
    vec4[1][0] = 1;

    vec2 = t1 * vec1;
    check(vec2 == vec3); //Checking matrix<T>-std::vector multiplication
    t1 *= vec1;
    check(t1 == vec4); //Checking *=
    t2 *= 5;
    check(t2 == t4); //Checking matrix<T>-number multiplication

    matrix<double> t6 = t2;
    check(t6 == t2);//Copying initializer check

    matrix<double> t7 = t2;
    t7 = t3;
    check(t7 == t3);//Copying operator check(same dimensions)

    matrix<double> t8(2,4);
    t8 = t4;
    check(t8 == t4);//Copying operator check(dimensions differ)

    t8 = t8;
    check(t8 == t4);//Copying to itself check

    matrix<double> t9 = std::move(t8);//Moving constructor check
    check(t9 == t4);
    check(t8.nullptrCheck());

    t9 = std::move(t9);
    check(t9 == t4);//Moving to itself check

    matrix<double> t10 = t7;
    t10 = std::move(t9);
    check(t10 == t4);//Moving operator check
    check(t9.nullptrCheck());
    

    cout << "If no errors above - every function works properly" << endl;
    return 0;
}

