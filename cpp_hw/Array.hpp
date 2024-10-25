#pragma once

#include <stdexcept>
#include <cstddef>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t Sz>
class Array {
 public:
  T data[Sz];

  T const& operator[](size_t idx) const {
    return data[idx];
  }

  T const& At(size_t idx) const {
    if (idx >= Sz) {
      throw ArrayOutOfRange{};
    }
    return data[idx];
  }

  T& operator[](size_t idx) {
    return data[idx];
  }

  T& At(size_t idx) {
    if (idx >= Sz) {
      throw ArrayOutOfRange{};
    }
    return data[idx];
  }

  T& Front() {
    return data[0];
  }

  T const& Front() const {
    return data[0];
  }

  T& Back() {
    return data[Sz - 1];
  }

  T const& Back() const {
    return data[Sz - 1];
  }

  T* Data() {
    return data;
  }

  const T* Data() const {
    return data;
  }

  size_t Size() const {
    return Sz;
  }

  template <size_t OtherSz>
  void Swap(Array<T, OtherSz>& other) {
    if (Sz != OtherSz) {
      return;
    }

    for (size_t i = 0; i < Sz; ++i) {
      T temp = other[i];
      other[i] = data[i];
      data[i] = temp;
    }
  }

  void Fill(const T& val) {
    for (size_t i = 0; i < Sz; ++i) {
      data[i] = val;
    }
  }

  bool Empty() const {
    return Sz == 0;
  }
};
