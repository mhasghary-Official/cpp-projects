// main.cpp
#include "Matrix.h"
#include <iostream>
#include <vector>

void displayMenu() {
    std::cout << "\n=== Matrix Calculator ===" << std::endl;
    std::cout << "1. Matrix Addition" << std::endl;
    std::cout << "2. Matrix Subtraction" << std::endl;
    std::cout << "3. Matrix Multiplication" << std::endl;
    std::cout << "4. Scalar Multiplication" << std::endl;
    std::cout << "5. Matrix Transpose" << std::endl;
    std::cout << "6. Matrix Determinant" << std::endl;
    std::cout << "7. Matrix Inverse" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Choose an operation: ";
}

Matrix inputMatrix(const std::string& name) {
    int rows, cols;
    std::cout << "Enter dimensions for " << name << " (rows columns): ";
    std::cin >> rows >> cols;
    
    std::vector<std::vector<double>> data(rows, std::vector<double>(cols));
    std::cout << "Enter matrix elements row by row:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> data[i][j];
        }
    }
    return Matrix(data);
}

void performAddition() {
    std::cout << "\n--- Matrix Addition ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    
    try {
        Matrix result = A + B;
        std::cout << "\nResult:" << std::endl;
        result.display();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void performSubtraction() {
    std::cout << "\n--- Matrix Subtraction ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    
    try {
        Matrix result = A - B;
        std::cout << "\nResult:" << std::endl;
        result.display();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void performMultiplication() {
    std::cout << "\n--- Matrix Multiplication ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    
    try {
        Matrix result = A * B;
        std::cout << "\nResult:" << std::endl;
        result.display();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void performScalarMultiplication() {
    std::cout << "\n--- Scalar Multiplication ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    double scalar;
    std::cout << "Enter scalar value: ";
    std::cin >> scalar;
    
    Matrix result = A * scalar;
    std::cout << "\nResult:" << std::endl;
    result.display();
}

void performTranspose() {
    std::cout << "\n--- Matrix Transpose ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    
    Matrix result = A.transpose();
    std::cout << "\nResult:" << std::endl;
    result.display();
}

void performDeterminant() {
    std::cout << "\n--- Matrix Determinant ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    
    try {
        double det = A.determinant();
        std::cout << "\nDeterminant: " << det << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void performInverse() {
    std::cout << "\n--- Matrix Inverse ---" << std::endl;
    Matrix A = inputMatrix("Matrix A");
    
    try {
        Matrix result = A.inverse();
        std::cout << "\nResult:" << std::endl;
        result.display();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                performAddition();
                break;
            case 2:
                performSubtraction();
                break;
            case 3:
                performMultiplication();
                break;
            case 4:
                performScalarMultiplication();
                break;
            case 5:
                performTranspose();
                break;
            case 6:
                performDeterminant();
                break;
            case 7:
                performInverse();
                break;
            case 8:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    } while (choice != 8);
    
    return 0;
}