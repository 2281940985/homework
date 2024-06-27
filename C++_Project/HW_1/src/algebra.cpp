#include "../include/algebra.h"
#include<iostream>
#include<iomanip>
#include<random>
using namespace std;
namespace algebra
{
    Matrix createMatrix(size_t n, size_t m, double val)
    {
        if(n <= 0 || m <= 0)
        {
            throw logic_error("wrong col or row\n");
        }
        Matrix mat(n, vector<double>(m, val));
        return mat;
    }
    Matrix zeros(size_t n, size_t m)
    {
        return createMatrix(n, m, 0);
    }
    Matrix ones(size_t n, size_t m)
    {
        return createMatrix(n, m, 1);
    }
    Matrix identity(size_t n)
    {
        Matrix mat = createMatrix(n, n, 0);
        for(int i = 0; i < n; i++)
        {
            mat[i][i] = 1;
        }
        return mat;
    }
    Matrix randon(size_t n, size_t m, double min, double max)
    {
        if(min > max)
        {
            throw logic_error("wrong min and max\n");
        }

        Matrix mat = zeros(n, m);
        default_random_engine generator;
        uniform_real_distribution<double> distribution(min, max);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                mat[i][j] = distribution(generator);
            }
        }
        return mat;
    }
    void display(const Matrix& matrix)
    {
        const int cellWidth = 5;
        for(auto mat_row : matrix)
        {
            for(auto val : mat_row)
            {
                cout << "|" << setw(cellWidth) << val << " ";
            }
            cout << "|" << endl;
        }
    }
    Matrix sum_sub(const Matrix& a, const Matrix& b, const std::string& operation)
    {
        if (a.size() != b.size() || a[0].size() != b[0].size()){
            throw std::logic_error("Matrices must have the same dimensions.");
        }
        Matrix mat = zeros(a.size(), a[0].size());
        if (operation == "sub") {
            for (std::size_t i = 0; i < a.size(); i++) {
                for (std::size_t j = 0; j < a[i].size(); ++j) {
                    mat[i][j] = a[i][j] - b[i][j];
                }
            } 
        } else {
            for (std::size_t i = 0; i < a.size(); i++) {
                for (std::size_t j = 0; j < a[i].size(); ++j) {
                    mat[i][j] = a[i][j] + b[i][j];
                }
            }
        }
        return mat;
    }
    Matrix multiply(const Matrix& a, double b)
    {
        Matrix mat = createMatrix(a.size(), a[0].size(), 0);
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = 0; j < a[0].size(); j++)
            {
                mat[i][j] = a[i][j] * b;
            }
        }
        return mat;
    }
    Matrix multiply(const Matrix& a, const Matrix& b)
    {
        if(a[0].size() != b.size())
        {
            throw logic_error("wrong size\n");
        }
        Matrix mat = createMatrix(a.size(), b[0].size(), 0);
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = 0; j < b[0].size(); j++)
            {
                for(int k = 0, q = 0; k < a[i].size(), q < b.size(); k++, q++)
                {
                    
                    mat[i][j] += a[i][k] *  b[q][j]; 
                    
                }
            }
        }
        return mat;
    }
    Matrix handamard_product(const Matrix& a, const Matrix& b)
    {
        if(a.size() != b.size() || a[0].size() != b[0].size())
        {
            throw logic_error("wrong size\n");
        }
        Matrix mat = createMatrix(a.size(), a[0].size(), 0);
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = 0; j < a[0].size(); ++j)
            {
                mat[i][j] = a[i][j] * b[i][j];
            }
        }
        return mat;
    }
    Matrix transpose(const Matrix& a)
    {
        Matrix mat = zeros(a.size(), a[0].size());
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = 0; j < a[0].size(); ++j)
            {
                mat[i][j] = a[j][i];
            }
        }
        return mat;
    }
    double trace(const Matrix& a)
    {
        if(a.size() != a[0].size())
        {
            throw logic_error("wrong size\n");
        }
        double tr = 0;
        for(int i = 0; i < a.size(); i++)
        {
            tr += a[i][i];
        }
        return tr;
    }
    double determinant(const Matrix& a)
    {
        if(a.size() != a[0].size())
        {
            throw logic_error("wrong size\n");
        }
        if(a.size() == 1) return a[0][0];
        double det = 0;
        for(int i = 0; i < a[0].size(); ++i)
        {
            Matrix mat = a;
            mat.erase(mat.begin());
            for(int j = 0; j < mat.size(); ++j)
            {
                mat[j].erase(mat[j].begin() + i);
            }
            det += a[0][i] * pow(-1, i) * determinant(mat);
        }
        return det;
    }
    Matrix inverse(const Matrix& a)
    {
        if(a.size() != a[0].size())
        {
            throw logic_error("wrong size\n");
        }
        if(determinant(a) == 0)
        {
            throw logic_error("determinant is zero\n");
        }
        Matrix mat = zeros(a.size(), a[0].size());
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = 0; j < a[0].size(); ++j)
            {
                Matrix tmp = a;
                tmp.erase(tmp.begin()+i);
                for(int i = 0; i < tmp.size(); i++)
                {
                    tmp[i].erase(tmp[i].begin()+j);
                }
                mat[i][j] = determinant(tmp) * pow(-1, i+j);
            }
        }
        return multiply(transpose(mat), 1.0/determinant(a));
    }

} // namespace algebra


