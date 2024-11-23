#include <cmath>
#include <iostream>

int main() {
  int64_t n, k;
  std::cin >> n >> k;
  int64_t l = 0;
  int64_t r = 10e16;
  while (l < r) {
    int64_t m = l + (r - l) / 2;

    std::cout << l << " " << m << " " << r << '\n';
    int64_t s = 0;
    for (size_t p = 1; std::pow(k, p) < m; p++) {
      if (p % 2 == 1) {
        s += m / std::pow(k, p);
      } else {
        s -= m / std::pow(k, p);
      }
    }
    if (s < n) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  std::cout << l << '\n';
  return 0;
}
