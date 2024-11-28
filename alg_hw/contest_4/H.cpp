#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>

struct Pair {
  double a;
  double b;
};

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<Pair> rates(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> rates[i].a >> rates[i].b;
  }

  std::vector<double> roubles(n);
  std::vector<double> dollars(n);
  std::vector<double> euro(n);

  roubles[0] = 100.f;

  for (size_t i = 1; i < n + 1; ++i) {
    double r_usd = rates[i - 1].a;
    double r_eur = rates[i - 1].b;

    roubles[i] = std::max({roubles[i - 1], dollars[i - 1] * r_usd, euro[i - 1] * r_eur});
    dollars[i] = std::max({dollars[i - 1], roubles[i - 1] / r_usd, euro[i - 2] * (r_eur / r_usd)});
    euro[i] = std::max({euro[i - 1], dollars[i - 1] * (r_usd / r_eur), roubles[i - 1] / r_eur});
  }

  std::cout << std::fixed << std::setprecision(3) << roubles[n] << '\n';
}
