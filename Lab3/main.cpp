#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;



#ifndef CMATRIX_H
#define CMATRIX_H

#include <stdio.h>

long long ciagFibonacciego(int n)
{
    long long a = 0, b = 1, zwracanaSuma = 0;

    for (int i = 0; i < n; i++)    {
        
        zwracanaSuma += b;
        b += a; // b = a+b
        a = b - a; //a staje sie b(a+b)
       
        
    }

    return zwracanaSuma;
}

template <class T>
class CMatrix
{
public:
    CMatrix(int rows, int cols)
    {
        
        setRow(rows);
        setCol(cols);
        setMod(10);//Modulo hard coded

        data = new T * [rows]; 

        for (int i = 0; i < row; i++) {
            data[i] = new T[cols]; 
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0; 
            }
        }
    }

    void print();
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    void setMod(int m) { M = m; } //Modulo
    T& operator()(int row, int col);
    CMatrix& operator+(CMatrix m);
    CMatrix& operator*(CMatrix m);
private:
    T** data;
    int row, col;
    int M;//Modulo
};


template <class T>
void CMatrix<T>::print()
{
    int i, j;

    for (i = 0; i < row; i++) 
    {
        for (j = 0; j < col; j++) 
        {
            printf("%.1f    ", (float)data[i][j]);
        }
        printf("\n");
    }
}


template<class T> T& CMatrix<T>::operator()(int row, int col)
{
    return data[row][col];
}

template<class T> CMatrix<T> &CMatrix<T>::operator+(CMatrix<T> m)
{
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            data[i][j] = data[i][j] % M;
            data[i][j] += m.data[i][j]%M;//dodawanie modulo M=10
        }
    }
    return *this;
}

template<class T> CMatrix<T>& CMatrix<T>::operator*(CMatrix<T> m)
{
    CMatrix<T> temp(row, m.col);
    int i, j, k;
    for (i = 0; i < temp.row; i++) {
        for (j = 0; j < temp.col; j++) {
            temp.data[i][j] = 0;
            for (k = 0; k < col; k++)
                temp.data[i][j] += data[i][k] * m.data[k][j];
        }
    }

    return (*this = temp);
}



#endif 
//otrzymana liczba w wyniku operacji fibonacci(Indeks ciagu S) % modulo M daja wartosc sumy wyrazow ciagu fibonacciego do przekazanego funkcji indeksu
//C == 1, czyli ciag An ma kolejne wartosci jak ciag fibonacciego  liczba M to modulo, liczba T ile wyrazow ciagu An(ciagu fibonacciego) 
int main()
{
   std::cout<<ciagFibonacciego(1)%10<<"\n";
    
    /*
    CMatrix<long long> m(3, 3);
    m.print();
    cout << "\n";
    CMatrix<long long> m1(3, 3);
    cout << "\n";
    m1.print();
    //m(1, 1) = 2;
    cout << "\n";
    m(1, 1) = 2;
    m = m + m1;
    m.print();
    cout << m(1,1);
    */
    

    
}




