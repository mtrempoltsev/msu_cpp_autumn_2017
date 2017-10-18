#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix
{
private:
    class vec{
    public:
        vec();
        vec(unsigned int);
        ~vec();
        double& operator[](unsigned int i);
        const double& operator[](unsigned int i) const;
    private:
        unsigned int rows;
        double* values;
    };
public:
    Matrix(unsigned int, unsigned int);
    Matrix(const Matrix&);
    Matrix::vec& operator[](unsigned int i);
    const Matrix::vec& operator[](unsigned int i) const;
    Matrix& operator*(int) const;
    std::vector<double>& operator*(const std::vector<double>&) const;
    Matrix& operator*=(int);
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;
    unsigned int getRowsNum() const;
    unsigned int getColumnsNum() const;
    void setToIdentity();
    virtual ~Matrix();
private:

    unsigned int rows;
    unsigned int columns;
    vec* values;
};

#endif // MATRIX_H
