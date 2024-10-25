#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Polynomial {
 public:
  using Container = typename std::vector<T>;
  using ConstIterator = typename Container::const_iterator;

 private:
  Container coeffs_;
  inline static const T valueTypeZero{0};  // NOLINT

  void DeleteZeroes() {
    while (!coeffs_.empty() && coeffs_.back() == valueTypeZero) {
      coeffs_.pop_back();
    }
  }

 public:
  Polynomial(const Container& coeffs) : coeffs_(coeffs) {  // NOLINT
    DeleteZeroes();
  }

  Polynomial(const T& value = {}) {  // NOLINT
    if (value != valueTypeZero) {
      coeffs_.push_back(value);
    }
  }

  template <typename ForwardIt>
  Polynomial(ForwardIt first, ForwardIt last) : coeffs_{first, last} {
    DeleteZeroes();
  }

  const Container& GetCoeffs() const {
    return coeffs_;
  }

  friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    return lhs.coeffs_ == rhs.coeffs_;
  }

  friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
  }

  Polynomial& operator+=(const Polynomial& other) {
    if (other.Degree() > Degree()) {
      coeffs_.resize(other.Degree() + 1);
    }
    for (size_t i = 0; i < other.coeffs_.size(); i++) {
      coeffs_[i] += other.coeffs_[i];
    }
    DeleteZeroes();
    return *this;
  }

  Polynomial& operator-=(const Polynomial& other) {
    if (other.Degree() > Degree()) {
      coeffs_.resize(other.Degree() + 1);
    }
    for (size_t i = 0; i < other.coeffs_.size(); i++) {
      coeffs_[i] -= other.coeffs_[i];
    }
    DeleteZeroes();
    return *this;
  }

  Polynomial& operator*=(const Polynomial& other) {
    if (Degree() == -1 || other.Degree() == -1) {
      coeffs_.resize(0);
    }
    Container tmp(Degree() + other.Degree() + 1);
    for (int i = 0; i <= Degree(); ++i) {
      for (int j = 0; j <= other.Degree(); ++j) {
        tmp[i + j] += coeffs_[i] * other.coeffs_[j];
      }
    }
    coeffs_ = std::move(tmp);
    DeleteZeroes();
    return *this;
  }

  friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
    return lhs += rhs;
  }

  friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
    return lhs -= rhs;
  }

  friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs) {
    return lhs *= rhs;
  }

  const T& operator[](size_t pow) const {
    if (pow >= coeffs_.size()) {
      return valueTypeZero;
    }
    return coeffs_[pow];
  }

  T operator()(const T& value) const {
    T result = valueTypeZero;

    for (int i = Degree(); i >= 0; --i) {
      result *= value;
      result += coeffs_[i];  // a_0 + x(a_1 + x(a_2 + x(a_3 + x(a_4 + x(...))))) x(a_n-1 + x*(0 + a_n))
    }

    return result;
  }

  int Degree() const {
    return static_cast<int>(coeffs_.size()) - 1;
  }

  ConstIterator begin() const {  // NOLINT
    return coeffs_.cbegin();
  }

  ConstIterator end() const {  // NOLINT
    return coeffs_.cend();
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& poly) {
  T zero{0};
  T one{1};
  T minus{-1};

  if (poly.GetCoeffs().empty()) {
    out << 0;
    return out;
  }

  for (int i = poly.Degree(); i >= 0; --i) {
    if (poly.GetCoeffs()[i] == zero) {
      continue;
    }

    if ((poly.GetCoeffs()[i] > zero) && (i < poly.Degree())) {
      out << '+';
    }

    if (i == 0) {
      out << poly.GetCoeffs()[i];
      continue;
    }

    if (poly.GetCoeffs()[i] == minus) {
      out << '-';
    }

    if (!(poly.GetCoeffs()[i] == one || poly.GetCoeffs()[i] == minus)) {
      out << poly.GetCoeffs()[i] << '*';
    }

    out << 'x';

    if (i > 1) {
      out << '^' << i;
    }
  }
  return out;
}
