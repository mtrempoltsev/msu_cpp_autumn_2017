#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

class row{
public:
    row(size_t elem, double* ptr):
            elem(elem),v(ptr){}
    ~row(){
        free(v);
    }
    double& operator[](const size_t pos){
        if(pos >= elem){
            assert(!"index out of range");;
        }
        return v[pos];
    }
private:
    size_t elem;
    double *v;

};

class matrix{
public:
    matrix(size_t rows, size_t cols):
            rows(rows),cols(cols)
    {
        if((cols < 1)||(rows < 1))
            assert(!"index out of range");
        a = new double[rows*cols];
        memset(a, 0, sizeof(double) * rows * cols);
    }

    ~matrix(){
        free(a);
    }

    int getRows(){
        return this->rows;
    }

    int getColumns(){
        return this->cols;
    }

    row& operator[](const size_t val){
        if(val >= (*this).rows)
            assert(!"index out of range");
        row* v = new row(cols, a+val*cols);
        return *v;
    }

    matrix& operator*=(const int rval){
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                (*this)[i][j] *= rval;
            }
        }
        return *this;
    }

    matrix& operator*(const int rval){
        matrix* res = new matrix(rows, cols);
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                (*res)[i][j] = (*this)[i][j] * rval;
            }
        }
        return *res;
    }

    vector<double>& operator*=(const vector<double> &rval){
        if(cols != rval.size()){
            assert(!"index out of range");
        }
        vector<double>* res = new vector<double>(rows);
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                (*res)[i] += (*this)[i][j] * rval[j];
            }
        }
        delete(this);
        return *res;
    }

    vector<double>& operator*(const vector<double> &rval){
        if(cols != rval.size()){
            assert(!"index out of range");
        }
        vector<double>* res = new vector<double>(rows);
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < cols; j++){
                (*res)[i] += (*this)[i][j] * rval[j];
            }
        }
        return *res;
    }


    bool operator==(matrix &rval){
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

    bool operator!=(matrix &rval){
        return !(*this == rval);
    }

private:
    size_t rows;
    size_t cols;
    double *a;
};

void check(bool value)
{
    if (!value)
        cout << "error" << endl;
}

int main() {
    matrix t1(2, 2);

    t1[0][0] = 1;
    t1[0][1] = 2;
    t1[1][0] = 3;
    t1[1][1] = 4;

    matrix t2(2, 2);
    t2[0][0] = 1;
    t2[0][1] = 2;
    t2[1][0] = 3;
    t2[1][1] = 4;

    matrix t3(2, 2);
    t3[0][0] = 1;
    t3[0][1] = 2;
    t3[1][0] = 2;
    t3[1][1] = 4;

    matrix t4(2, 2);
    t4[0][0] = 5;
    t4[0][1] = 10;
    t4[1][0] = 15;
    t4[1][1] = 20;

    check(t1[0][0] == 1); //Checking element acquisition ([])
    check(t1 == t2); //Checking comparision (==)
    check(t1 != t3); //Checking comparision (!=)

    matrix t5(15, 10);
    check(t5.getRows() == 15); //Checking rows acquisition
    check(t5.getColumns() == 10); //Checking columns acquisition

    vector<double> vec1 = {-1, 1};
    vector<double> vec2(2);
    vector<double> vec3 = {1, 1};

    vec2=t1 * vec1;
    check(vec2 == vec3); //Checking matrix-std::vector multiplication
    t2 *= 5;
    check(t2 == t4); //Checking matrix-number multiplication

    cout << "If no errors above - every function works properly" << endl;
    return 0;
}

