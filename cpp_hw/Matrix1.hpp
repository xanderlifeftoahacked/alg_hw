#pragma once

#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t Rows, size_t Columns>
class Matrix {
 public:
  T data[Rows][Columns];

  size_t RowsNumber() const {
    return Rows;
  }
  size_t ColumnsNumber() const {
    return Columns;
  }

  const T& operator()(size_t row, size_t column) const {
    return data[row][column];
  }

  T& operator()(size_t row, size_t column) {
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

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, Columns>& operator+=(const Matrix<T, OtherRows, OtherColumns>& other) {
    if (OtherRows != Rows || OtherColumns != Columns) {
      throw MatrixIsDegenerateError{};
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        data[i][j] += other.data[i][j];
      }
    }
    return *this;
  }

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, Columns> operator+(const Matrix<T, OtherRows, OtherColumns>& other) const {
    Matrix result = *this;
    result += other;
    return result;
  }

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, Columns>& operator-=(const Matrix<T, OtherRows, OtherColumns>& other) {
    if (OtherRows != Rows || OtherColumns != Columns) {
      throw MatrixIsDegenerateError{};
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        data[i][j] -= other.data[i][j];
      }
    }
    return *this;
  }

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, Columns> operator-(const Matrix<T, OtherRows, OtherColumns>& other) const {
    Matrix result = *this;
    result -= other;
    return result;
  }

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, OtherColumns> operator*(const Matrix<T, OtherRows, OtherColumns>& other) const {
    if (Columns != OtherRows) {
      throw MatrixIsDegenerateError{};
    }
    Matrix<T, Rows, OtherColumns> result{};

    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < OtherColumns; ++j) {
        T sum = 0;
        for (size_t k = 0; k < Columns; ++k) {
          sum += data[i][k] * other.data[k][j];
        }
        result.data[i][j] = sum;
      }
    }

    return result;
  }

  template <size_t OtherRows, size_t OtherColumns>
  Matrix<T, Rows, OtherColumns>& operator*=(const Matrix<T, OtherRows, OtherColumns>& other) {
    if (Columns != OtherRows) {
      throw MatrixIsDegenerateError{};
    }

    *this = *this * other;
    return *this;
  }

  Matrix& operator*=(const T& scalar) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        data[i][j] *= scalar;
      }
    }
    return *this;
  }

  Matrix operator*(const T& scalar) const {
    Matrix result = *this;
    result *= scalar;
    return result;
  }

  Matrix& operator/=(const T& scalar) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        data[i][j] /= scalar;
      }
    }
    return *this;
  }

  Matrix operator/(const T& scalar) const {
    Matrix result = *this;
    result /= scalar;
    return result;
  }

  friend Matrix operator*(const T& scalar, const Matrix& matrix) {
    return matrix * scalar;
  }

  bool operator==(const Matrix& other) const {
    if (other.RowsNumber() != Rows || other.ColumnsNumber() != Columns) {
      return false;
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        if (data[i][j] != other.data[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix& other) const {
    return !(*this == other);
  }

  friend std::istream& operator>>(std::istream& in, Matrix& matrix) {
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Columns; ++j) {
        in >> matrix(i, j);
      }
    }
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        if (j != Columns - 1) {
          out << matrix.data[i][j] << ' ';
        } else {
          out << matrix.data[i][j];
        }
      }
      out << std::string("\n");
    }
    return out;
  }
};

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(Matrix<T, Rows, Columns> matrix) {
  Matrix<T, Columns, Rows> result;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      result(j, i) = matrix(i, j);
    }
  }
  return result;
}
