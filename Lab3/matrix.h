#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

class Matrix {
public:
    Matrix(int, int);
    Matrix(long long**, int, int);
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);

    inline long long& operator()(int x, int y) { return p[x][y]; }

    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);



 

private:
    int rows_, cols_;
    long long** p;

    void allocSpace();
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif