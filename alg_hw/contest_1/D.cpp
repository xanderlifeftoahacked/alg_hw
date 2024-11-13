#include <cstdint>
#include <iostream>

int main() {
  size_t n = 0;
  std::cin >> n;

  uint64_t sum = (n + 1) * (n + 2) / 2;

  uint64_t cur = 0;
  while (n--) {
    std::cin >> cur;
    sum -= cur;
  }

  std::cout << sum << '\n';

  return 0;
}
