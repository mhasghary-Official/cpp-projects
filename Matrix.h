// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    // Constructors
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<double>>& input);
    
    // Basic operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    
    // Matrix operations
    Matrix transpose() const;
    Matrix inverse() const;
    double determinant() const;
    Matrix cofactor() const;
    Matrix adjoint() const;
    
    // Utility functions
    void display() const;
    bool isSquare() const;
    int getRows() const;
    int getCols() const;
    double& at(int row, int col);
    double at(int row, int col) const;
    
    // Static methods
    static Matrix identity(int size);
    static Matrix zeros(int rows, int cols);
    static Matrix ones(int rows, int cols);
    
private:
    Matrix getSubmatrix(int excludeRow, int excludeCol) const;
    double calculateDeterminant(const Matrix& mat) const;
};

#endif