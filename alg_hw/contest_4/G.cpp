#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

struct Triplet {
  int a;
  int b;
  int c;
};

int main() {
  size_t n = 0;

  std::cin >> n;

  std::vector<Triplet> people(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> people[i].a >> people[i].b >> people[i].c;
  }

  std::vector<int> dp(n + 1, std::numeric_limits<int>::max());
  dp[0] = 0;

  for (size_t i = 1; i < n + 1; ++i) {
    dp[i] = dp[i - 1] + people[i - 1].a;
    if (i > 1) {
      dp[i] = std::min(dp[i], dp[i - 2] + people[i - 2].b);
    }
    if (i > 2) {
      dp[i] = std::min(dp[i], dp[i - 3] + people[i - 3].c);
    }
  }

  for (auto elem : dp) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  std::cout << dp[n] << '\n';

  return 0;
}
