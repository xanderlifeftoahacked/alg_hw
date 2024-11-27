#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t n = 0, m = 0, q = 0;

  std::cin >> n >> m >> q;

  std::vector<std::vector<int64_t>> mat(n, std::vector<int64_t>(m));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> mat[i][j];
    }
  }

  std::vector<std::vector<int64_t>> dp(n + 1, std::vector<int64_t>(m + 1));

  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      dp[i][j] =
          mat[i - 1][j - 1] + dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
    }
  }

  size_t x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  while (q--) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] +
                     dp[x1 - 1][y1 - 1]
              << '\n';
  }

  return 0;
}
