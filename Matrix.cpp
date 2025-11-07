// Matrix.cpp
#include "Matrix.h"
#include <cmath>
#include <algorithm>

// Constructors
Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& input) {
    if (input.empty()) {
        rows = 0;
        cols = 0;
        return;
    }
    
    rows = input.size();
    cols = input[0].size();
    data = input;
    
    // Ensure all rows have the same number of columns
    for (const auto& row : input) {
        if (row.size() != cols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }
}

// Basic operations
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
    }
    
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// Matrix operations
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

double Matrix::determinant() const {
    if (!isSquare()) {
        throw std::invalid_argument("Determinant can only be calculated for square matrices");
    }
    return calculateDeterminant(*this);
}

Matrix Matrix::cofactor() const {
    if (!isSquare()) {
        throw std::invalid_argument("Cofactor matrix can only be calculated for square matrices");
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix submatrix = getSubmatrix(i, j);
            double det = submatrix.calculateDeterminant(submatrix);
            result.data[i][j] = pow(-1, i + j) * det;
        }
    }
    return result;
}

Matrix Matrix::adjoint() const {
    return cofactor().transpose();
}

Matrix Matrix::inverse() const {
    if (!isSquare()) {
        throw std::invalid_argument("Inverse can only be calculated for square matrices");
    }
    
    double det = determinant();
    if (fabs(det) < 1e-10) {
        throw std::invalid_argument("Matrix is singular, cannot calculate inverse");
    }
    
    Matrix adj = adjoint();
    return adj * (1.0 / det);
}

// Utility functions
void Matrix::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(10) << std::setprecision(4) << data[i][j];
        }
        std::cout << std::endl;
    }
}

bool Matrix::isSquare() const {
    return rows == cols;
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

double& Matrix::at(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data[row][col];
}

double Matrix::at(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data[row][col];
}

// Static methods
Matrix Matrix::identity(int size) {
    Matrix result(size, size);
    for (int i = 0; i < size; i++) {
        result.data[i][i] = 1.0;
    }
    return result;
}

Matrix Matrix::zeros(int rows, int cols) {
    return Matrix(rows, cols);
}

Matrix Matrix::ones(int rows, int cols) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = 1.0;
        }
    }
    return result;
}

// Private helper methods
Matrix Matrix::getSubmatrix(int excludeRow, int excludeCol) const {
    Matrix result(rows - 1, cols - 1);
    int r = 0;
    for (int i = 0; i < rows; i++) {
        if (i == excludeRow) continue;
        int c = 0;
        for (int j = 0; j < cols; j++) {
            if (j == excludeCol) continue;
            result.data[r][c] = data[i][j];
            c++;
        }
        r++;
    }
    return result;
}

double Matrix::calculateDeterminant(const Matrix& mat) const {
    int n = mat.rows;
    
    if (n == 1) {
        return mat.data[0][0];
    }
    if (n == 2) {
        return mat.data[0][0] * mat.data[1][1] - mat.data[0][1] * mat.data[1][0];
    }
    
    double det = 0.0;
    for (int j = 0; j < n; j++) {
        Matrix submatrix = mat.getSubmatrix(0, j);
        det += pow(-1, j) * mat.data[0][j] * calculateDeterminant(submatrix);
    }
    return det;
}