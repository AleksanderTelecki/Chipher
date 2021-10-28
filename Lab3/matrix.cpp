#include "matrix.h"
#include <stdexcept>
#include "matrix.h"

#define EPS 1e-10


using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = 0;
        }
    }
}

Matrix::Matrix(double** a, int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] p[i];
        }
        delete[] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                temp.p[i][j] += (p[i][k] * m.p[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix& Matrix::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] *= num;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] /= num;
        }
    }
    return *this;
}

Matrix Matrix::operator^(int num)
{
    Matrix temp(*this);
    return expHelper(temp, num);
}


#pragma region Trash
//
//void Matrix::swapRows(int r1, int r2)
//{
//    double* temp = p[r1];
//    p[r1] = p[r2];
//    p[r2] = temp;
//}
//
//Matrix Matrix::transpose()
//{
//    Matrix ret(cols_, rows_);
//    for (int i = 0; i < rows_; ++i) {
//        for (int j = 0; j < cols_; ++j) {
//            ret.p[j][i] = p[i][j];
//        }
//    }
//    return ret;
//}
//
//
//
//
//
//
//
//
///* STATIC CLASS FUNCTIONS
// ********************************/
//
//Matrix Matrix::createIdentity(int size)
//{
//    Matrix temp(size, size);
//    for (int i = 0; i < temp.rows_; ++i) {
//        for (int j = 0; j < temp.cols_; ++j) {
//            if (i == j) {
//                temp.p[i][j] = 1;
//            }
//            else {
//                temp.p[i][j] = 0;
//            }
//        }
//    }
//    return temp;
//}
//
//Matrix Matrix::solve(Matrix A, Matrix b)
//{
//    // Gaussian elimination
//    for (int i = 0; i < A.rows_; ++i) {
//        if (A.p[i][i] == 0) {
//            // pivot 0 - throw error
//            throw domain_error("Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again.");
//        }
//        for (int j = i + 1; j < A.rows_; ++j) {
//            for (int k = i + 1; k < A.cols_; ++k) {
//                A.p[j][k] -= A.p[i][k] * (A.p[j][i] / A.p[i][i]);
//                if (A.p[j][k] < EPS && A.p[j][k] > -1 * EPS)
//                    A.p[j][k] = 0;
//            }
//            b.p[j][0] -= b.p[i][0] * (A.p[j][i] / A.p[i][i]);
//            if (A.p[j][0] < EPS && A.p[j][0] > -1 * EPS)
//                A.p[j][0] = 0;
//            A.p[j][i] = 0;
//        }
//    }
//
//    // Back substitution
//    Matrix x(b.rows_, 1);
//    x.p[x.rows_ - 1][0] = b.p[x.rows_ - 1][0] / A.p[x.rows_ - 1][x.rows_ - 1];
//    if (x.p[x.rows_ - 1][0] < EPS && x.p[x.rows_ - 1][0] > -1 * EPS)
//        x.p[x.rows_ - 1][0] = 0;
//    for (int i = x.rows_ - 2; i >= 0; --i) {
//        int sum = 0;
//        for (int j = i + 1; j < x.rows_; ++j) {
//            sum += A.p[i][j] * x.p[j][0];
//        }
//        x.p[i][0] = (b.p[i][0] - sum) / A.p[i][i];
//        if (x.p[i][0] < EPS && x.p[i][0] > -1 * EPS)
//            x.p[i][0] = 0;
//    }
//
//    return x;
//}
//
//Matrix Matrix::bandSolve(Matrix A, Matrix b, int k)
//{
//    // optimized Gaussian elimination
//    int bandsBelow = (k - 1) / 2;
//    for (int i = 0; i < A.rows_; ++i) {
//        if (A.p[i][i] == 0) {
//            // pivot 0 - throw exception
//            throw domain_error("Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again.");
//        }
//        for (int j = i + 1; j < A.rows_ && j <= i + bandsBelow; ++j) {
//            int k = i + 1;
//            while (k < A.cols_ && A.p[j][k]) {
//                A.p[j][k] -= A.p[i][k] * (A.p[j][i] / A.p[i][i]);
//                k++;
//            }
//            b.p[j][0] -= b.p[i][0] * (A.p[j][i] / A.p[i][i]);
//            A.p[j][i] = 0;
//        }
//    }
//
//    // Back substitution
//    Matrix x(b.rows_, 1);
//    x.p[x.rows_ - 1][0] = b.p[x.rows_ - 1][0] / A.p[x.rows_ - 1][x.rows_ - 1];
//    for (int i = x.rows_ - 2; i >= 0; --i) {
//        int sum = 0;
//        for (int j = i + 1; j < x.rows_; ++j) {
//            sum += A.p[i][j] * x.p[j][0];
//        }
//        x.p[i][0] = (b.p[i][0] - sum) / A.p[i][i];
//    }
//
//    return x;
//}
//
//// functions on VECTORS
//double Matrix::dotProduct(Matrix a, Matrix b)
//{
//    double sum = 0;
//    for (int i = 0; i < a.rows_; ++i) {
//        sum += (a(i, 0) * b(i, 0));
//    }
//    return sum;
//}
//
//// functions on AUGMENTED matrices
//Matrix Matrix::augment(Matrix A, Matrix B)
//{
//    Matrix AB(A.rows_, A.cols_ + B.cols_);
//    for (int i = 0; i < AB.rows_; ++i) {
//        for (int j = 0; j < AB.cols_; ++j) {
//            if (j < A.cols_)
//                AB(i, j) = A(i, j);
//            else
//                AB(i, j) = B(i, j - B.cols_);
//        }
//    }
//    return AB;
//}
//
//
//
//
//Matrix Matrix::gaussianEliminate()
//{
//    Matrix Ab(*this);
//    int rows = Ab.rows_;
//    int cols = Ab.cols_;
//    int Acols = cols - 1;
//
//    int i = 0; // row tracker
//    int j = 0; // column tracker
//
//    // iterate through the rows
//    while (i < rows)
//    {
//        // find a pivot for the row
//        bool pivot_found = false;
//        while (j < Acols && !pivot_found)
//        {
//            if (Ab(i, j) != 0) { // pivot not equal to 0
//                pivot_found = true;
//            }
//            else { // check for a possible swap
//                int max_row = i;
//                double max_val = 0;
//                for (int k = i + 1; k < rows; ++k)
//                {
//                    double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
//                    if (cur_abs > max_val)
//                    {
//                        max_row = k;
//                        max_val = cur_abs;
//                    }
//                }
//                if (max_row != i) {
//                    Ab.swapRows(max_row, i);
//                    pivot_found = true;
//                }
//                else {
//                    j++;
//                }
//            }
//        }
//
//        // perform elimination as normal if pivot was found
//        if (pivot_found)
//        {
//            for (int t = i + 1; t < rows; ++t) {
//                for (int s = j + 1; s < cols; ++s) {
//                    Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
//                    if (Ab(t, s) < EPS && Ab(t, s) > -1 * EPS)
//                        Ab(t, s) = 0;
//                }
//                Ab(t, j) = 0;
//            }
//        }
//
//        i++;
//        j++;
//    }
//
//    return Ab;
//}


#pragma endregion


/* NON-MEMBER FUNCTIONS
 ********************************/

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}

Matrix operator/(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp /= num);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}
