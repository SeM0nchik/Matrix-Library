# Matrix-Library
A lightweight, header-only C++ template library for matrix operations. Supports basic arithmetic, transposition, determinants, inverses, and more for fixed-size matrices.

## Features
- Template-based matrix class with compile-time dimensions.
- Basic operations: addition, subtraction, multiplication, scalar operations.
- Square matrix operations: transpose, trace, determinant, inverse.
- Exception handling for out-of-range access and degenerate matrices.
- Input/output stream support for easy matrix I/O.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/matrix-lib.git
   ```
2. Include the headers in your project:
   ```cpp
   #include "matrix/matrix.hpp"
   #include "matrix/operations.hpp"
   #include "matrix/io.hpp"
   ```

## Usage
Here's a simple example to get started:

```cpp
#include <iostream>
#include "matrix/matrix.hpp"
#include "matrix/operations.hpp"
#include "matrix/io.hpp"

int main() {
    Matrix<double, 2, 2> m1;
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;

    Matrix<double, 2, 2> m2;
    m2(0, 0) = 5; m2(0, 1) = 6;
    m2(1, 0) = 7; m2(1, 1) = 8;

    // Addition
    auto sum = m1 + m2;
    std::cout << "Sum:\n" << sum;

    // Determinant
    std::cout << "Determinant of m1: " << Determinant(m1) << "\n";

    // Inverse
    auto inv = GetInversed(m1);
    std::cout << "Inverse of m1:\n" << inv;

    return 0;
}
```

## Directory Structure
- `include/matrix/`: Header files for the library.
  - `exceptions.hpp`: Custom exception classes.
  - `matrix.hpp`: Core matrix class and basic operations.
  - `functions.hpp`: Square matrix operations (transpose, trace, determinant, inverse).
  - `io.hpp`: Input/output stream operators.

## Contributing
Contributions are welcome! Please open an issue or submit a pull request.

## License
This project is licensed under the MIT License.
