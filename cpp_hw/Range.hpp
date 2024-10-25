#pragma once

class Range {
 public:
  class Iterator {
   public:
    struct ForwardIteratorTag {};
    using iterator_category = ForwardIteratorTag;  // NOLINT
    using difference_type = int;                   // NOLINT
    using value_type = int;                        // NOLINT
    using pointer = const int*;                    // NOLINT
    using reference = const int&;                  // NOLINT

    Iterator(int current, int step) : current_(current), step_(step) {
    }

    reference operator*() const {
      return current_;
    }

    pointer operator->() const {
      return &current_;
    }

    Iterator& operator++() {
      current_ += step_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) {
      if (a.step_ > 0) {
        return a.current_ >= b.current_;
      }
      return a.current_ <= b.current_;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return !(a == b);
    }

   private:
    int current_;
    int step_;
  };

  explicit Range(int end) : begin_(0), end_(end), step_(1) {
  }
  explicit Range(int begin, int end) : begin_(begin), end_(end), step_(1) {
  }
  explicit Range(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
    if (step == 0) {
      begin_ = 0;
      end_ = 0;
    }
  }

  Iterator begin() const {  // NOLINT
    return {begin_, step_};
  }

  Iterator end() const {  // NOLINT
    return {end_, step_};
  }

 private:
  int begin_;
  int end_;
  int step_;
};
