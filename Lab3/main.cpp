#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
long long c, mod;


#ifndef CMATRIX_H
#define CMATRIX_H

#include <stdio.h>

long long ciagFibonacciego(int n)
{
    long long a = 1, b = 1, zwracanaSuma = 1;
     
        for (int i = 0; i < n-1; i++) {            
                zwracanaSuma += b;
                b = b +  a*c; 
                a = b - a; 
            
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

    friend ostream& operator<<(ostream& output, CMatrix& macierzA);
    void print();
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    T& operator()(int row, int col);
    CMatrix& operator+(CMatrix m);
    CMatrix& operator*(CMatrix m);
 

    CMatrix matPow(CMatrix x, long long k) {

        vector<int>digs;
        while (k > 0)
        {
            digs.push_back(k % 2);
            k /= 2;
        }
        reverse(digs.begin(), digs.end());
        CMatrix ans = x;

        for (int i = 1; i < (int)digs.size(); i++)
        {
            ans = ans * ans;
            if (digs[i])
            {
                ans = ans * x;
            }
        }
        return ans;
    }

private:
    T** data;
    int row, col;

};

ostream& operator<<(ostream& output, CMatrix<long long>& macierz) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            output << " " << macierz.data[i][j];
        }
        output << endl;
    }
    //output << endl;

    return output;
}

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
            data[i][j] = (data[i][j] + m.data[i][j]) % mod;
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
            {
                temp.data[i][j] += (data[i][k] * m.data[k][j]);
            }
            temp.data[i][j] %= mod;
               
        }
    }

    return (*this = temp);
}

#endif 

void print(vector<long long> lVector) {

    cout << "\n";
    for (int i = 0; i < lVector.size(); i++)
    {
        cout << lVector[i] << "\n";
    }

}

int main()
{
   int t;

   scanf_s("%lld %lld", &c, &mod);
   scanf_s("%d", &t);

   long long number;
   vector<long long> answers(t);

   CMatrix<long long> m(3, 3);
   m(0, 0) = c;
   m(0, 1) = 1;
   m(0, 2) = 1;
   m(1, 0) = 1;
   m(1, 1) = 0;
   m(1, 2) = 0;
   m(2, 0) = 0;
   m(2, 1) = 0;
   m(2, 2) = 1;

   CMatrix<long long> m1(3, 3);
   m1(0, 0) = ciagFibonacciego(2);
   m1(0, 1) = 0;
   m1(0, 2) = 0;
   m1(1, 0) = ciagFibonacciego(1);
   m1(1, 1) = 0;
   m1(1, 2) = 0;
   m1(2, 0) = 2 - c;
   m1(2, 1) = 0;
   m1(2, 2) = 0;

   CMatrix<long long> mWynik(3, 3);

   for (int  i = 0; i < t; i++)
   {
       scanf_s("%lld", &number);

       if (number == 1) {
           answers[i] = 1;
           continue;
       }
       if (number == 2) {
           answers[i] = 2;
           continue;
       }

       mWynik = m.matPow(m, number - 1) * m1;

       answers[i] = mWynik(1, 0);
   } 
   

   print(answers);
  
   cout << "\n"<< "Macierze:"<<"\n";

   cout << m << " *\n"<< m1 << " =\n"<< mWynik;
  
}




