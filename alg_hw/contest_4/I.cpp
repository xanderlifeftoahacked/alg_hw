#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  size_t n = 0, s = 0;
  std::cin >> n;

  std::vector<uint64_t> banknotes(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> banknotes[i];
  }

  std::cin >> s;

  std::vector<uint64_t> dp(s + 1, std::numeric_limits<uint64_t>::max());
  std::vector<uint64_t> path(s + 1, 0);
  dp[0] = 0;

  for (size_t i = 1; i < s + 1; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (banknotes[j] <= i && dp[i - banknotes[j]] != std::numeric_limits<uint64_t>::max() &&
          dp[i - banknotes[j]] + 1 < dp[i]) {
        dp[i] = dp[i - banknotes[j]] + 1;
        path[i] = banknotes[j];
      }
    }
  }

  if (dp[s] != std::numeric_limits<uint64_t>::max()) {
    std::cout << dp[s] << '\n';
  } else {
    std::cout << "-1\n";
  }

  size_t i = s;
  while (path[i] != 0) {
    std::cout << path[i] << ' ';
    i -= path[i];
  }
  std::cout << '\n';

  return 0;
}
