#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include "exceptions.hpp"

template<class T, size_t Rows, size_t Columns>
class Matrix {
public:
    T data[Rows][Columns]{};

    static size_t RowsNumber() {
        return Rows;
    }
    static size_t ColumnsNumber() {
        return Columns;
    }
    T& operator()(size_t row, size_t column) {
        return data[row][column];
    }
    const T& operator()(size_t row, size_t column) const {
        return data[row][column];
    }
    T& At(size_t row, size_t column) {
        if (row >= Rows || column >= Columns) {
            throw MatrixOutOfRange();
        }
        return data[row][column];
    }
    const T& At(size_t row, size_t column) const {
        if (row >= Rows || column >= Columns) {
            throw MatrixOutOfRange();
        }
        return data[row][column];
    }
    auto operator+(const Matrix<T, Rows, Columns>& other) const {
        Matrix<T, Rows, Columns> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    auto operator+(const Matrix<T, Rows, Columns>&& other) const {
        Matrix<T, Rows, Columns> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    auto operator-(const Matrix<T, Rows, Columns>& other) const {
        Matrix<T, Rows, Columns> result{};
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    auto operator-(const Matrix<T, Rows, Columns>&& other) const {
        Matrix<T, Rows, Columns> result{};
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    template<size_t ColumnsOther>
    auto operator*(const Matrix<T, Columns, ColumnsOther>& other) const {
        Matrix<T, Rows, ColumnsOther> result{};
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < ColumnsOther; ++j) {
                for (size_t k = 0; k < Columns; ++k) {
                    result(i, j) += this->At(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
    auto operator+=(const Matrix<T, Rows, Columns>& other) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }
    auto operator-=(const Matrix<T, Rows, Columns>& other) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }
    auto operator*=(const T& scalar) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }
    auto operator/=(const T& scalar) {
        if (scalar == 0) {
            throw MatrixIsDegenerateError();
        }
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                data[i][j] /= scalar;
            }
        }
        return *this;
    }
    auto operator*=(const Matrix<T, Columns, Columns>& other) {
        T array[Rows][Columns]{};
        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = 0; j < Columns; j++) {
                for (size_t k = 0; k < Columns; k++) {
                    array[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = 0; j < Columns; j++) {
                this->data[i][j] = array[i][j];
            }
        }
        return *this;
    }
    bool operator==(const Matrix<T, Rows, Columns>& other) const {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Columns; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix<T, Rows, Columns>& other) const {
        return !(*this == other);
    }
};
template<class T, size_t Rows, size_t Columns>
auto operator*(const Matrix<T, Rows, Columns>& matrix, const double scalar) {
    Matrix<T, Rows, Columns> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(i, j) = matrix(i, j) * scalar;
        }
    }
    return result;
}

template<class T, size_t Rows, size_t Columns>
auto operator*(const Matrix<T, Rows, Columns>&& matrix, const double scalar) {
    Matrix<T, Rows, Columns> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(i, j) = matrix(i, j) * scalar;
        }
    }
    return result;
}

template<class T, size_t Rows, size_t Columns>
auto operator*(const double scalar, Matrix<T, Rows, Columns>& matrix) {
    Matrix<T, Rows, Columns> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(i, j) = matrix(i, j) * scalar;
        }
    }
    return result;
}

template<class T, size_t Rows, size_t Columns>
auto operator*(const double scalar, Matrix<T, Rows, Columns>&& matrix) {
    Matrix<T, Rows, Columns> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(i, j) = matrix(i, j) * scalar;
        }
    }
    return result;
}

template<class T, size_t Rows, size_t Columns, class S>
auto operator/(const Matrix<T, Rows, Columns>& matrix, const S scalar) {
    if (scalar == 0) {
        throw MatrixIsDegenerateError();
    }
    Matrix<T, Rows, Columns> result{};
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result(i, j) = matrix(i, j) / scalar;
        }
    }
    return result;
}
#endif