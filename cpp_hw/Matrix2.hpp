#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class Matrix {
  std::vector<std::vector<T>> data_;

 public:
  // ПО-ДРУГОМУ НИКАК(
  class Iterator;
  class ConstIterator;

  Iterator begin() {  // NOLINT
    return Iterator(data_.begin(), data_.end(), data_.begin()->begin());
  }

  Iterator end() {  // NOLINT
    return Iterator(data_.end(), data_.end(), {});
  }

  ConstIterator begin() const {  // NOLINT
    return ConstIterator(data_.begin(), data_.end(), data_.begin()->begin());
  }

  ConstIterator end() const {  // NOLINT
    return ConstIterator(data_.end(), data_.end(), {});
  }

  explicit Matrix(const std::vector<std::vector<T>>& data) : data_(data) {
  }

  std::pair<std::size_t, std::size_t> size() const {  // NOLINT
    return {data_.size(), data_[0].size()};
  }

  Matrix<T>& operator+=(const Matrix<T>& other) {
    assert("Not possible to add" && data_[0].size() == other.data_[0].size() && data_.size() == other.data_);
    for (size_t i = 0; i < data_.size(); ++i) {
      for (size_t j = 0; j < data_[i].size(); ++j) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return *this;
  }

  Matrix<T> operator+(const Matrix<T>& other) const {
    Matrix<T> result = *this;
    result += other;
    return result;
  }

  template <typename Scalar>
  Matrix<T>& operator*=(const Scalar& scalar) {
    for (size_t i = 0; i < data_.size(); ++i) {
      for (size_t j = 0; j < data_[i].size(); ++j) {
        data_[i][j] *= scalar;
      }
    }
    return *this;
  }

  template <typename Scalar>
  Matrix<T> operator*(const Scalar& scalar) const {
    Matrix<T> result = *this;
    result *= scalar;
    return result;
  }

  Matrix& operator*=(const Matrix& other) {
    assert("Not possible to multiply" && data_[0].size() == other.data_.size());

    std::vector<std::vector<T>> result(data_.size(), std::vector<T>(other.data_[0].size(), 0));

    for (size_t i = 0; i < data_.size(); ++i) {
      for (size_t k = 0; k < data_[i].size(); ++k) {
        for (size_t j = 0; j < other.data_[0].size(); ++j) {
          result[i][j] += data_[i][k] * other.data_[k][j];
        }
      }
    }
    data_ = std::move(result);
    return *this;
  }

  Matrix operator*(const Matrix& other) const {
    Matrix result = *this;
    result *= other;
    return result;
  }

  Matrix<T>& transpose() {  // NOLINT
    std::vector<std::vector<T>> transposed_data(data_[0].size(), std::vector<T>(data_.size()));
    for (size_t i = 0; i < data_.size(); ++i) {
      for (size_t j = 0; j < data_[i].size(); ++j) {
        transposed_data[j][i] = data_[i][j];
      }
    }
    data_ = std::move(transposed_data);
    return *this;
  }

  Matrix<T> transposed() const {  // NOLINT
    Matrix<T> result = *this;
    result.transpose();
    return result;
  }

  friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
    for (size_t i = 0; i < m.data_.size(); ++i) {
      for (size_t j = 0; j < m.data_[i].size(); ++j) {
        out << m.data_[i][j];
        if (j != m.data_[i].size() - 1) {
          out << '\t';
        }
      }
      if (i != m.data_.size() - 1) {
        out << '\n';
      }
    }
    return out;
  }
};

template <typename T>
class Matrix<T>::Iterator {
  using RowIterator = typename std::vector<T>::iterator;
  using OuterIterator = typename std::vector<std::vector<T>>::iterator;

  OuterIterator outer_;
  OuterIterator outer_end_;
  RowIterator inner_;

 public:
  Iterator(OuterIterator outer, OuterIterator outer_end, RowIterator inner)
      : outer_(outer), outer_end_(outer_end), inner_(inner) {
  }

  Iterator& operator++() {
    ++inner_;
    if (inner_ == outer_->end()) {
      ++outer_;
      if (outer_ != outer_end_) {
        inner_ = outer_->begin();
      }
    }
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  T& operator*() {
    return *inner_;
  }

  bool operator==(const Iterator& other) const {
    return outer_ == other.outer_ && (outer_ == outer_end_ || inner_ == other.inner_);
  }

  bool operator!=(const Iterator& other) const {
    return !(*this == other);
  }
};

template <typename T>
class Matrix<T>::ConstIterator {
  using RowIterator = typename std::vector<T>::const_iterator;
  using OuterIterator = typename std::vector<std::vector<T>>::const_iterator;

  OuterIterator outer_;
  OuterIterator outer_end_;
  RowIterator inner_;

 public:
  ConstIterator(OuterIterator outer, OuterIterator outer_end, RowIterator inner)
      : outer_(outer), outer_end_(outer_end), inner_(inner) {
  }

  ConstIterator& operator++() {
    ++inner_;
    if (inner_ == outer_->end()) {
      ++outer_;
      if (outer_ != outer_end_) {
        inner_ = outer_->begin();
      }
    }
    return *this;
  }

  ConstIterator operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  const T& operator*() const {
    return *inner_;
  }

  bool operator==(const ConstIterator& other) const {
    return outer_ == other.outer_ && (outer_ == outer_end_ || inner_ == other.inner_);
  }

  bool operator!=(const ConstIterator& other) const {
    return !(*this == other);
  }
};
