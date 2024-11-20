#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<size_t> zeros_on_prefix(n + 1);

  int temp = 0;
  for (size_t i = 1; i < n + 1; ++i) {
    std::cin >> temp;
    zeros_on_prefix[i] = zeros_on_prefix[i - 1] + (temp == 0);
  }

  size_t k = 0, l = 0, r = 0;

  std::cin >> k;

  while (k--) {
    std::cin >> l >> r;
    std::cout << zeros_on_prefix[r] - zeros_on_prefix[l - 1] << ' ';
  }

  std::cout << '\n';

  return 0;
}
