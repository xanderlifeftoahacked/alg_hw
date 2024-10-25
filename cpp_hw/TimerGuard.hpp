#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

class TimerGuard {
 private:
  std::string message_;
  std::ostream& out_;
  std::chrono::high_resolution_clock::time_point start_time_;

 public:
  explicit TimerGuard(std::string_view message = "", std::ostream& out = std::cout)
      : message_(message), out_(out), start_time_(std::chrono::high_resolution_clock::now()) {
  }

  ~TimerGuard() {
    using namespace std::chrono;
    auto end_time = high_resolution_clock::now();
    double duration = static_cast<double>(duration_cast<milliseconds>(end_time - start_time_).count());
    out_ << message_ << " " << duration / 1000 << '\n';
  }
};
