#include "hw1.h"
#include <random>
#include <iomanip>
#include <iostream>
#include <assert.h>


Matrix algebra::zeros(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 0.0));
}

Matrix algebra::ones(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 1.0));
}

Matrix algebra::random(size_t n, size_t m, double min, double max) {
    if (min > max) { throw std::logic_error("max must be greater than min"); }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    Matrix mat(n, std::vector<double>(m));
    for (auto& row : mat)
        for (auto& elem : row)
            elem = dis(gen);    
    return mat;
}

Matrix algebra::show(const Matrix &matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row)
            std::cout << std::setw(5) << std::setprecision(3) << elem << ' ';
        std::cout << std::endl;
    }
    return matrix;
}

Matrix algebra::multiply(const Matrix &matrix, double c) {
    Matrix result(matrix);
    for (auto& row : result) {
        for (auto& elem : row)
            elem *= c;
    }
    return result;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.size() == 0 || matrix2.size() == 0) {
        return Matrix{};
    }
    int col = matrix1.size();
    int row = matrix2[0].size();
    int t = matrix1[0].size();
    if (t != matrix2.size()) {
        throw std::logic_error("incorrect dimensions");
    }
    Matrix result = zeros(col, row);
    for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
            for (size_t k = 0; k < t; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

Matrix algebra::sum(const Matrix& matrix, double c) {
    Matrix result(matrix);
    for (auto& row : result) {
        for (auto& elem : row)
            elem += c;
    }
    return result;
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.size() == 0 && matrix2.size() == 0) {
        return Matrix{};
    }
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::logic_error("incorrect dimensions");
    }
    Matrix result(matrix1);
    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix1[0].size(); j++) {
            result[i][j] += matrix2[i][j];
        }
    }
    return result;
}

Matrix algebra::transpose(const Matrix& matrix) {
    if (matrix.empty()) {
        return Matrix();
    }
    Matrix result(matrix[0].size(), std::vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m) {
    if (n >= matrix.size() || m >= matrix[0].size()) {
        throw std::logic_error("out of range");
    }
    Matrix result(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (i < n && j < m) {
                result[i][j] = matrix[i][j];
            } else if (i < n && j > m) {
                result[i][j - 1] = matrix[i][j];
            } else if (i > n && j < m) {
                result[i - 1][j] = matrix[i][j];
            } else if (i > n && j > m) {
                result[i - 1][j - 1] = matrix[i][j];
            }
        }
    }
    return result;
}

double algebra::determinant(const Matrix& matrix) {
    if (matrix.size() == 0) {
        return 1;
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("incorrect dimensions");
    }
    if (matrix.size() == 1) {
        return matrix[0][0];
    }
    if (matrix.size() == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0;
    for (size_t i = 0; i < matrix.size(); i++) {
        Matrix minor = algebra::minor(matrix, 0, i);
        det += matrix[0][i] * pow(-1, i) * algebra::determinant(minor);
    }
    return det;
}

Matrix algebra::inverse(const Matrix& matrix) {
    if (matrix.size() == 0) {
        return matrix;
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("incorrect dimensions");
    }
    double det = algebra::determinant(matrix);
    if (det == 0) {
        throw std::logic_error("determinant is zero");
    }
    Matrix result(matrix.size(), std::vector<double>(matrix[0].size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            Matrix minor = algebra::minor(matrix, i, j);
            result[j][i] = pow(-1, i + j) * algebra::determinant(minor) / det;
        }
    }
    return result;
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    if (axis == 0) {
        if (matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("incorrect dimensions");
        }
        Matrix result(matrix1);
        for (size_t i = 0; i < matrix2.size(); i++) {
            result.push_back(matrix2[i]);
        }
        return result;
    } else if (axis == 1) {
        if (matrix1.size() != matrix2.size()) {
            throw std::logic_error("incorrect dimensions");
        }
        Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size()));
        for (size_t i = 0; i < matrix1.size(); i++) {
            for (size_t j = 0; j < matrix1[0].size(); j++) {
                result[i][j] = matrix1[i][j];
            }
            for (size_t j = 0; j < matrix2[0].size(); j++) {
                result[i][j + matrix1[0].size()] = matrix2[i][j];
            }
        }
        return result;
    } else {
        throw std::logic_error("incorrect axis");
    }
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    if (r1 >= matrix.size() || r2 >= matrix.size()) {
        throw std::logic_error("out of range");
    }
    Matrix result(matrix);
    std::swap(result[r1], result[r2]);
    return result;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c) {
    if (r >= matrix.size()) {
        throw std::logic_error("out of range");
    }
    Matrix result(matrix);
    for (size_t i = 0; i < matrix[r].size(); i++) {
        result[r][i] *= c;
    }
    return result;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    if (r1 >= matrix.size() || r2 >= matrix.size()) {
        throw std::logic_error("out of range");
    }
    Matrix result(matrix);
    for (size_t i = 0; i < matrix[r1].size(); i++) {
        result[r2][i] += c * matrix[r1][i];
    }
    return result;
}

Matrix algebra::upper_triangular(const Matrix& matrix) {
    if (matrix.size() == 0) {
        return matrix;
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("incorrect dimensions");
    }
    Matrix result(matrix);
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = i + 1; j < matrix.size(); j++) {
            double c = -result[j][i] / result[i][i];
            result = algebra::ero_sum(result, i, c, j);
        }
    }
    return result;
};