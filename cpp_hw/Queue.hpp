#pragma once
#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue {
 private:
  Container container_;

 public:
  Queue() = default;

  const T& front() const {  // NOLINT
    return container_.front();
  }

  T& front() {  // NOLINT
    return container_.front();
  }

  void pop() {  // NOLINT
    container_.pop_front();
  }

  void push(const T& value) {  // NOLINT
    container_.push_back(value);
  }

  std::size_t size() const {  // NOLINT
    return container_.size();
  }

  bool empty() const {  // NOLINT
    return container_.empty();
  }

  bool operator==(const Queue& other) const {
    return container_ == other.container_;
  }

  bool operator!=(const Queue& other) const {
    return container_ != other.container_;
  }
};
