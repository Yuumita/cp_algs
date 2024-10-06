#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Matrix {
public:
    int rows, cols;
    vector<vector<T>> mat;
    Matrix();
    Matrix(int r, int c, T val = T(0)) : rows(r), cols(c) {
        mat.assign(r, vector<T>(c, val));
    }


    Matrix& operator+=(const Matrix &rhs) { 
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                this->mat[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix &rhs) { 
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                this->mat[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix &rhs) { 
        Matrix res(rows, rhs.cols);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < rhs.cols; j++) {
                res[i][j] = T(0);
                for(int k = 0; k < cols; k++) {
                    res[i][j] += this->mat[i][k] * rhs[k][j];
                }
            }
        }
        return (*this) = res;
    }
    Matrix operator-() const { return Matrix(rows, cols, 0) -= *this; }

    Matrix operator+(Matrix x) const { return Matrix(*this) += x; }
    Matrix operator*(Matrix x) const { return Matrix(*this) *= x; }
    Matrix operator-(Matrix x) const { return Matrix(*this) -= x; }

    vector<T>& operator[](const int i) { return mat[i]; }

    static Matrix Identity(int n) {
        Matrix res(n, n);
        for(int i = 0; i < n; i++) res[i][i] = T(1);
        return res;
    }

    Matrix pow(long long exp) {
        Matrix res = Matrix::Identity(rows);
        Matrix *base = *this;
        while(exp > 0) {
            if(exp & 1) res *= base;
            base *= base, exp >>= 1;

        }
        return res;
    }
};

 
int main(){
}