#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "matrix.hpp"
#include <iostream>
template<class T, size_t Rows, size_t Columns>
std::istream& operator>>(std::istream& is, Matrix<T, Rows, Columns>&& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            is >> matrix(i, j);
        }
    }
    return is;
}

template<class T, size_t Rows, size_t Columns>
std::istream& operator>>(std::istream& is, Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            is >> matrix(i, j);
        }
    }
    return is;
}

template<class T, size_t Rows, size_t Columns>
std::ostream& operator<<(std::ostream& os, Matrix<T, Rows, Columns>&& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            os << matrix(i, j);
            if (j + 1 < Columns) {
                os << " ";
            }
        }
        os << '\n';
    }
    return os;
}

template<class T, size_t Rows, size_t Columns>
std::ostream& operator<<(std::ostream& os, Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            os << matrix(i, j);
            if (j + 1 < Columns) {
                os << " ";
            }
        }
        os << '\n';
    }
    return os;
}

#endif