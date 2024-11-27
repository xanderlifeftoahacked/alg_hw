#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n = 0, m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (matrix[i][j] == 0) {
        continue;
      }
      dp[i][j] = 1 + std::min({dp[i + 1][j + 1], dp[i][j + 1], dp[i + 1][j]});
      ans = std::max(ans, dp[i][j]);
    }
  }

  std::cout << ans << '\n';

  return 0;
}
