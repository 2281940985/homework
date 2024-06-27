#ifndef ALGEBRA_H
#define ALGEBRA_H
#include <vector>
#include <optional>
#include <string>
namespace algebra {
    using Matrix =  std::vector<std::vector<double>>;
    Matrix createMatrix(size_t n, size_t m, double val);
    Matrix zeros(size_t n, size_t m);

    Matrix ones(size_t n, size_t m);
    Matrix identity(size_t n);
    Matrix randon(size_t n, size_t m, double min, double max);

    void display(const Matrix& matrix);
    Matrix sum_sub(const Matrix& a, const Matrix& b, const std::string& operation = "sum");
    Matrix multiply(const Matrix& a, double b);
    Matrix multiply(const Matrix& a, const Matrix& b);
   
    Matrix handamard_product(const Matrix& a, const Matrix& b);
    Matrix transpose(const Matrix& a);
    double trace(const Matrix& a);
    double determinant(const Matrix& a);
    Matrix inverse(const Matrix& a);
}
#endif