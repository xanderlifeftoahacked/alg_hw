#include <algorithm>
#include <iomanip>
#include <iostream>
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

  std::vector<double> roubles(n + 1);
  std::vector<double> dollars(n + 1);
  std::vector<double> euro(n + 1);

  roubles[0] = 100.0f;
  for (size_t i = 1; i < n + 1; ++i) {
    double r_usd = rates[i - 1].a;
    double r_eur = rates[i - 1].b;

    roubles[i] =
        std::max({roubles[i - 1], dollars[i - 1] * r_usd, euro[i - 1] * r_eur});
    dollars[i] = std::max({dollars[i - 1], roubles[i - 1] / r_usd,
                           euro[i - 1] * (r_eur / r_usd)});
    euro[i] = std::max({euro[i - 1], dollars[i - 1] * (r_usd / r_eur),
                        roubles[i - 1] / r_eur});
  }

  std::cout << std::fixed << std::setprecision(2) << roubles[n] << '\n';
}
