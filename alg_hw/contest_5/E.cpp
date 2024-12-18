#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

std::vector<int64_t> manacher(std::vector<char> &str) {
  int64_t right = 0;
  int64_t center = 0;

  std::vector<int64_t> dp(str.size(), 0);

  for (int64_t i = 0; i < dp.size(); ++i) {
    int64_t mirr = 2 * center - i;

    if (i < right) {
      dp[i] = std::min(dp[mirr], right - i);
    }

    while (str[i - (dp[i] + 1)] == str[i + (dp[i] + 1)]) {
      ++dp[i];
    }

    if (i + dp[i] > right) {
      right = i + dp[i];
      center = i;
    }
  }

  return dp;
}

int main() {
  size_t n = 0, m = 0;
  std::cin >> n >> m;

  std::vector<int> cubes(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> cubes[i];
  }

  std::vector<char> word;

  word.push_back('!');
  word.push_back('#');
  for (const auto ch : cubes) {
    word.push_back(ch);
    word.push_back('#');
  }
  word.push_back('?');
  std::vector<int64_t> res = manacher(word);

  size_t ans = 0;

  for (auto elem : res) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  for (const auto elem : res) {
    ans += (elem + 1) / 2;
  }

  ans -= cubes.size();

  std::cout << ans << '\n';

  return 0;
}
