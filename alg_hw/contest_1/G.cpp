#include <cstdint>
#include <iostream>

int main() {
  size_t n = 0;
  std::cin >> n;

  int32_t shift = 3 * 10e6;
  uint64_t accumulator = 0;

  int32_t cur = 0;
  while (n--) {
    std::cin >> cur;
    accumulator ^= (cur + shift);
  }

  std::cout << accumulator - shift << '\n';

  return 0;
}
