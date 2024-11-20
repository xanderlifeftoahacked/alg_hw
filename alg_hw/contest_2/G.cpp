#include <cstdint>
#include <iostream>

uint64_t count_interesting_before(int64_t val, int64_t k) {
  int64_t denominator = k;
  int sign = 1;
  uint64_t ans = 0;
  while (val / denominator > 0) {
    ans += val / denominator * sign;
    denominator *= k;
    sign *= -1;
  }
  return ans;
}

int main() {
  size_t n = 0;
  uint64_t k = 0;

  std::cin >> n >> k;

  uint64_t left = 0;
  uint64_t right = static_cast<uint64_t>(10e16);

  while (left < right - 1) {
    uint64_t mid = left + (right - left) / 2;
    if (count_interesting_before(mid, k) < n) {
      left = mid;
    } else {
      right = mid;
    }
  }

  std::cout << right << '\n';

  return 0;
}
