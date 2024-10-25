#pragma once

#include <cstdint>
#include <compare>
#include <iostream>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {

  int32_t numerator_;
  int32_t denominator_;

  static int32_t Abs(int32_t);

  static int32_t Gcd(int32_t, int32_t);

  static Rational Reduce(Rational);
  void Reduce();

 public:
  Rational();

  Rational(int32_t);  // NOLINT

  Rational(int32_t, int32_t);

  int32_t GetNumerator() const;
  int32_t GetDenominator() const;
  void SetNumerator(int32_t);
  void SetDenominator(int32_t);

  Rational operator+() const;
  Rational operator-() const;

  Rational &operator*=(const Rational &);
  Rational &operator/=(const Rational &);

  std::strong_ordering operator<=>(const Rational &) const;

  bool operator==(const Rational &other) const;
  bool operator!=(const Rational &other) const;
  bool operator>=(const Rational &other) const;
  bool operator<=(const Rational &other) const;
  bool operator>(const Rational &other) const;
  bool operator<(const Rational &other) const;

  friend Rational operator+(const Rational &, const Rational &);

  friend Rational operator-(const Rational &, const Rational &);

  friend Rational operator*(const Rational &, const Rational &);

  friend Rational operator/(const Rational &, const Rational &);

  Rational &operator+=(const Rational &);

  Rational &operator-=(const Rational &);

  Rational &operator++();
  Rational operator++(int);

  Rational &operator--();

  Rational operator--(int);

  friend std::ostream &operator<<(std::ostream &, const Rational &);

  friend std::istream &operator>>(std::istream &, Rational &);
};

inline Rational::Rational() : numerator_(0), denominator_(1) {
}

inline Rational::Rational(int32_t numerator) : numerator_(numerator), denominator_(1) {
}

inline Rational::Rational(int32_t numerator, int32_t denominator) : numerator_(numerator), denominator_(denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  this->Reduce();
}

inline int32_t Rational::GetNumerator() const {
  return numerator_;
}

inline int32_t Rational::GetDenominator() const {
  return denominator_;
}

inline void Rational::SetNumerator(int32_t val) {
  numerator_ = val;
  this->Reduce();
}

inline void Rational::SetDenominator(int32_t val) {

  if (val == 0) {
    throw RationalDivisionByZero{};
  }

  this->denominator_ = val;

  this->Reduce();
}

inline Rational Rational::Reduce(Rational obj) {
  if (obj.denominator_ < 0) {
    obj.numerator_ = -obj.numerator_;
    obj.denominator_ = -obj.denominator_;
  }

  int32_t gcd = Gcd(obj.numerator_, obj.denominator_);
  obj.numerator_ /= gcd;
  obj.denominator_ /= gcd;
  return obj;
};

inline int32_t Rational::Abs(int32_t value) {
  int32_t temp = value >> 31;

  value ^= temp;
  value += temp & 1;

  return value;
}

inline int32_t Rational::Gcd(int32_t a, int32_t b) {
  while (b != 0) {
    int32_t temp = b;
    b = a % b;
    a = temp;
  }
  return Abs(a);
}

inline void Rational::Reduce() {
  if (this->denominator_ < 0) {
    this->numerator_ = -this->numerator_;
    this->denominator_ = -this->denominator_;
  }
  int32_t gcd = Gcd(this->numerator_, this->denominator_);
  this->numerator_ /= gcd;
  this->denominator_ /= gcd;
}

inline Rational Rational::operator+() const {
  return *this;
}

inline Rational Rational::operator-() const {
  return Rational::Reduce({-numerator_, denominator_});
}

inline Rational operator+(const Rational &lhs, const Rational &rhs) {
  return Rational::Reduce(
      {lhs.numerator_ * rhs.denominator_ + rhs.numerator_ * lhs.denominator_, lhs.denominator_ * rhs.denominator_});
}

inline Rational operator-(const Rational &lhs, const Rational &rhs) {
  return Rational::Reduce(
      {lhs.numerator_ * rhs.denominator_ - rhs.numerator_ * lhs.denominator_, lhs.denominator_ * rhs.denominator_});
}

inline Rational operator*(const Rational &lhs, const Rational &rhs) {
  return Rational::Reduce({lhs.numerator_ * rhs.numerator_, lhs.denominator_ * rhs.denominator_});
}

inline Rational operator/(const Rational &lhs, const Rational &rhs) {
  return Rational::Reduce({lhs.numerator_ * rhs.denominator_, lhs.denominator_ * rhs.numerator_});
}

inline Rational &Rational::operator+=(const Rational &other) {
  *this = *this + other;
  this->Reduce();
  return *this;
}

inline Rational &Rational::operator-=(const Rational &other) {
  *this = *this - other;
  this->Reduce();
  return *this;
}

inline Rational &Rational::operator*=(const Rational &other) {
  *this = *this * other;
  this->Reduce();
  return *this;
}

inline Rational &Rational::operator/=(const Rational &other) {
  *this = *this / other;
  this->Reduce();
  return *this;
}

inline std::strong_ordering Rational::operator<=>(const Rational &other) const {
  return (numerator_ * other.denominator_) <=> (other.numerator_ * denominator_);
}

inline bool Rational::operator==(const Rational &other) const {
  return (*this <=> other) == std::strong_ordering::equal;
}

inline bool Rational::operator!=(const Rational &other) const {
  return !(*this == other);
}

inline bool Rational::operator<(const Rational &other) const {
  return (*this <=> other) == std::strong_ordering::less;
}

inline bool Rational::operator>(const Rational &other) const {
  return (*this <=> other) == std::strong_ordering::greater;
}

inline bool Rational::operator<=(const Rational &other) const {
  return !(*this > other);
}

inline bool Rational::operator>=(const Rational &other) const {
  return !(*this < other);
}

inline Rational &Rational::operator++() {
  numerator_ += denominator_;
  this->Reduce();
  return *this;
}

inline Rational Rational::operator++(int) {
  Rational temp = *this;
  ++(*this);
  this->Reduce();
  return temp;
}

inline Rational &Rational::operator--() {
  numerator_ -= denominator_;
  this->Reduce();
  return *this;
}

inline Rational Rational::operator--(int) {
  Rational temp = *this;
  --(*this);
  this->Reduce();
  return temp;
}

inline std::ostream &operator<<(std::ostream &os, const Rational &obj) {
  if (obj.denominator_ != 1) {
    os << obj.GetNumerator() << '/' << obj.GetDenominator();
  } else {
    os << obj.GetNumerator();
  }
  return os;
}

inline std::istream &operator>>(std::istream &is, Rational &obj) {
  std::string str;
  is >> str;

  if (str.find('/') == std::string::npos) {
    obj.SetNumerator(std::stoi(str));
    obj.SetDenominator(1);
    return is;
  }

  obj.SetNumerator(std::stoi(str.substr(0, str.find('/'))));
  obj.SetDenominator(std::stoi(str.substr(str.find('/') + 1, str.size())));
  obj.Reduce();

  return is;
}
