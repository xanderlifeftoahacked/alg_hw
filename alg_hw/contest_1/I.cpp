#include <array>
#include <cmath>
#include <iostream>

std::string ask_question(int d) {
  std::cout << "? " << d << std::endl;
  std::string level, side;
  std::cin >> level >> side;
  return side;
}

template <size_t Sz>
size_t bin_search(const std::array<int, Sz> &vec, int target) {
  int left = -1;
  int right = Sz;

  while (left < right - 1) {
    size_t mid = left + (right - left) / 2;

    if (target >= vec[mid]) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return right;
}
int main() {
  const int max_place = 54, min_place = 1;

  constexpr int step_max = (1 + 35);
  constexpr int step_min = -(54 - 36);
  std::array<int, (step_max - step_min) / 2> steps;

  std::cout << "? 0" << std::endl;
  std::string level, side, prev_side;
  std::cin >> level >> prev_side;

  int start = 0;
  if (level == "high") {
    start = step_min;
  } else {
    start = step_min + 1;
  }

  for (size_t i = 0; i < steps.size(); ++i) {
    steps[i] = start + (i * 2);
  }

  int left = 0, right = steps.size() - 1;
  if (prev_side == "main") {
    left = bin_search(steps, 0);
  } else {
    right = bin_search(steps, 0);
  }

  int prev_steps = 0;
  int mid = 0;
  int queries = 5;
  while (queries--) {
    mid = left + (right - left) / 2;
    side = ask_question(steps[mid] - prev_steps);
    if (prev_side == side && side == "main" ||
        prev_side != side && side == "main") {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
    prev_steps = steps[mid];
    prev_side = side;
  }

  std::cout << "! " << 36 - steps[right] << '\n';
  return 0;
}
