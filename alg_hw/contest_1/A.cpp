#include <iostream>

int main() {
  size_t ans = 0;
  size_t size = 0;

  std::cin >> size;
  ans = size + (1 + (size * 2 + 1)) * (size + 1) / 2;

  std::cout << ans << '\n';
  return 0;
}
