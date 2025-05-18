#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.hpp"
#include "exceptions.hpp"

template<class T, size_t Rows, size_t Columns>
auto GetTransposed(const Matrix<T, Rows, Columns>& matrix) {
    Matrix<T, Columns, Rows> result;
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(j, i) = matrix(i, j);
        }
    }
    return result;
}

template<class T, size_t Rows>
void Transpose(Matrix<T, Rows, Rows>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = i + 1; j < Rows; ++j) {
            if (i != j) {
                std::swap(matrix(i, j), matrix(j, i));
            }
        }
    }
}

template<class T, size_t Rows>
T Trace(const Matrix<T, Rows, Rows>& matrix) {
    T result{};
    for (size_t i = 0; i < Rows; ++i) {
        result += matrix.At(i, i);
    }
    return result;
}

template<class T, size_t Rows>
T Determinant(Matrix<T, Rows, Rows>& input) {
    Matrix<T, Rows, Rows> matrix = input;
    T result = 1;
    int32_t swaps = 0;
    T pivot = T();
    size_t pivot_row = 0;
    for (size_t i = 0; i < Rows; ++i) {
        pivot = matrix.At(i, i);
        pivot_row = i;
        for (size_t k = i + 1; k < Rows; ++k) {
            if (matrix.At(k, i) < pivot && matrix.At(k, i) > -pivot && matrix.At(k, i) != 0) {
                pivot = matrix.At(k, i);
                pivot_row = k;
            }
        }
        if (pivot == 0) {
            return 0;
        }
        if (pivot_row != i) {
            for (size_t t = 0; t < Rows; ++t) {
                std::swap(matrix.At(i, t), matrix.At(pivot_row, t));
            }
            swaps += 1;
        }
        result *= matrix.At(i, i);
        for (size_t l = i + 1; l < Rows; ++l) {
            T factor = matrix.At(l, i) / matrix.At(i, i);
            for (size_t m = i; m < Rows; ++m) {
                matrix.At(l, m) -= factor * matrix.At(i, m);
            }
        }
    }
    result *= (swaps % 2 == 0) ? 1 : -1;
    return result;
}

template<class T>
Matrix<T, 1, 1> GetInversed(Matrix<T, 1, 1>& input) {
    if (Determinant(input) == 0) {
        throw MatrixIsDegenerateError();
    }
    return input / Determinant(input) / Determinant(input);
}

template<class T, size_t Rows>
auto GetInversed(Matrix<T, Rows, Rows>& input) {
    if (Determinant(input) == 0) {
        throw MatrixIsDegenerateError();
    }
    Matrix<T, Rows - 1, Rows - 1> matrix;
    Matrix<T, Rows, Rows> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Rows; ++j) {
            size_t x = 0;
            size_t y = 0;
            for (size_t k = 0; k < Rows; ++k) {
                if (k == i) {
                    continue;
                }
                y = 0;
                for (size_t l = 0; l < Rows; ++l) {
                    if (l == j) {
                        continue;
                    }
                    matrix.At(x, y) = input.At(k, l);
                    y++;
                }
                x++;
            }
            result.At(i, j) = (i + j) % 2 == 0 ? Determinant(matrix) : -Determinant(matrix);
        }
    }
    return GetTransposed(result / Determinant(input));
}

template<class T, size_t Rows>
auto Inverse(Matrix<T, Rows, Rows>& matrix) {
    if (Determinant(matrix) == 0) {
        throw MatrixIsDegenerateError();
    }
    matrix = GetInversed(matrix);
    return matrix;
}

#endif