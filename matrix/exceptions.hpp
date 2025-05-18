#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <stdexcept>

class MatrixOutOfRange : public std::out_of_range {
public:
    MatrixOutOfRange() : std::out_of_range("Matrix index out of range") {}
};

class MatrixIsDegenerateError : public std::runtime_error {
public:
    MatrixIsDegenerateError() : std::runtime_error("Matrix is degenerate") {}
};

#endif