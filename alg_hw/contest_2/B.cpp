#include <cstdint>
#include <iostream>

int main() {
  size_t x;
  std::cin >> x;

  uint64_t max_value = 0;
  size_t count = 0;
  size_t i = 1, j = 1;

  while (count++ < x) {
    uint64_t val_a = i * i;
    uint64_t val_b = j * j * j;

    if (val_a < val_b) {
      max_value = std::max(max_value, val_a);
      ++i;
    } else if (val_a > val_b) {
      max_value = std::max(max_value, val_b);
      ++j;
    } else {
      max_value = std::max(max_value, val_a);
      ++i;
      ++j;
    }
  }

  std::cout << max_value << '\n';

  return 0;
}
