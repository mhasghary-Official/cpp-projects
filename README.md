# Matrix Calculator in C++

A comprehensive matrix calculator implementation in C++ that supports various matrix operations with an interactive command-line interface.

__Features__

_Basic Operations_

· ✅ Matrix Addition
· ✅ Matrix Subtraction
· ✅ Matrix Multiplication
· ✅ Scalar Multiplication

_Advanced Operations_

· ✅ Matrix Transpose
· ✅ Matrix Determinant
· ✅ Matrix Inverse
· ✅ Cofactor Matrix
· ✅ Adjoint Matrix

_Utility Functions_

· ✅ Identity Matrix Generation
· ✅ Zero Matrix Generation
· ✅ Ones Matrix Generation
· ✅ Matrix Display with Formatting
· ✅ Input Validation and Error Handling

__Project Structure__

```
matrix-calculator/
├── Matrix.h          # Header file with class declaration
├── Matrix.cpp        # Implementation of matrix operations
├── main.cpp          # Main program with user interface
└── README.md         # This file
```

__Class Documentation__

Matrix Class

Constructors

· Matrix() - Default constructor
· Matrix(int rows, int cols) - Create matrix with specified dimensions
· Matrix(const vector<vector<double>>& input) - Create matrix from 2D vector

Operator Overloads

· Matrix operator+(const Matrix& other) - Matrix addition
· Matrix operator-(const Matrix& other) - Matrix subtraction
· Matrix operator*(const Matrix& other) - Matrix multiplication
· Matrix operator*(double scalar) - Scalar multiplication

Matrix Operations

· Matrix transpose() - Returns transpose of the matrix
· Matrix inverse() - Returns inverse of the matrix
· double determinant() - Returns determinant value
· Matrix cofactor() - Returns cofactor matrix
· Matrix adjoint() - Returns adjoint matrix

Utility Methods

· void display() - Pretty-print matrix to console
· bool isSquare() - Check if matrix is square
· int getRows(), getCols() - Get dimensions
· double& at(int row, int col) - Access element with bounds checking

Static Methods

· Matrix identity(int size) - Create identity matrix
· Matrix zeros(int rows, int cols) - Create zero matrix
· Matrix ones(int rows, int cols) - Create matrix of ones

__Installation & Compilation__

Prerequisites

· C++ compiler (g++ recommended)
· C++11 or later standard

Compilation

```bash
# Compile the program
g++ -o matrix_calculator main.cpp Matrix.cpp -std=c++11

# Run the program
./matrix_calculator
```

_Alternative Build Methods_

Using Make (create Makefile):

```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = matrix_calculator
SOURCES = main.cpp Matrix.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
```

Using CMake (create CMakeLists.txt):

```cmake
cmake_minimum_required(VERSION 3.10)
project(MatrixCalculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(matrix_calculator main.cpp Matrix.cpp)
```

__Usage Examples__

Program Interface

When you run the program, you'll see an interactive menu:

```
=== Matrix Calculator ===
1. Matrix Addition
2. Matrix Subtraction
3. Matrix Multiplication
4. Scalar Multiplication
5. Matrix Transpose
6. Matrix Determinant
7. Matrix Inverse
8. Exit
Choose an operation:
```

Code Examples

Creating Matrices:

```cpp
// Create a 2x2 matrix
Matrix A(2, 2);
A.at(0, 0) = 1; A.at(0, 1) = 2;
A.at(1, 0) = 3; A.at(1, 1) = 4;

// Create from vector
vector<vector<double>> data = {{1, 2}, {3, 4}};
Matrix B(data);

// Special matrices
Matrix I = Matrix::identity(3);    // 3x3 identity
Matrix Z = Matrix::zeros(2, 3);    // 2x3 zeros
Matrix O = Matrix::ones(2, 2);     // 2x2 ones
```

Performing Operations:

```cpp
Matrix A = {{1, 2}, {3, 4}};
Matrix B = {{5, 6}, {7, 8}};

// Addition
Matrix C = A + B;

// Multiplication  
Matrix D = A * B;

// Transpose
Matrix E = A.transpose();

// Determinant
double det = A.determinant();

// Inverse
Matrix inv = A.inverse();
```

__Mathematical Background__

Determinant Calculation

Uses recursive Laplace expansion for matrices larger than 2x2:

```
For 2x2: det = a*d - b*c
For nxn: det = Σ(-1)^(i+j) * a_ij * det(M_ij)
```

Matrix Inverse

Calculated using the adjugate method:

```
A^(-1) = (1/det(A)) * adj(A)
```

Transpose

Element positions are swapped across the main diagonal:

```
A^T[i][j] = A[j][i]
```

__Error Handling__

The calculator includes comprehensive error checking:

· Dimension Validation: Ensures compatible dimensions for operations
· Square Matrix Check: Verifies matrices are square for determinant/inverse
· Non-singular Check: Prevents inverse calculation for singular matrices
· Bounds Checking: Validates array access indices
· Input Validation: Checks user input for correct formatting

__Limitations__

· Currently uses double precision floating-point arithmetic
· Determinant calculation may be slow for very large matrices (> 10x10)
· No support for complex numbers
· No file I/O for saving/loading matrices
· No eigenvalue/eigenvector calculations

__Future Enhancements__

Potential improvements for this calculator:

· Eigenvalue and eigenvector calculation
· LU decomposition
· QR decomposition
· Matrix rank calculation
· File I/O support
· Complex number support
· GUI interface
· Performance optimizations for large matrices

__Contributing__

Feel free to contribute to this project by:

1. Reporting bugs
2. Suggesting new features
3. Submitting pull requests
4. Improving documentation

__License__

This project is open source and available under the GPL 3.0 License.

__Academic Use__

implementationntation is suitable for:

· Linear algebra courses
· C++ programming practice
· Algorithm implementation studies
· Mathematical computing projects

The code emphasizes readability and educational value while maintaining proper software engineering practices.
