#include <cstdint>
#include <iostream>

double power(double a, int32_t n) {
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return a;
  }

  if (n % 2 == 0) {
    return power(a * a, n / 2);
  }
  return a * power(a, n - 1);
}

int main() {
  double a = 0;
  int32_t n = 0;

  std::cin >> a >> n;

  std::cout << power(a, n) << '\n';

  return 0;
}
