#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<uint64_t> prices(n + 1);
  prices[0] = 0;

  for (size_t i = 1; i < n + 1; ++i) {
    std::cin >> prices[i];
  }

  for (size_t i = 2; i < n + 1; ++i) {
    prices[i] = std::min(prices[i - 1], prices[i - 2]) + prices[i];
  }

  std::cout << prices[n] << '\n';

  return 0;
}
