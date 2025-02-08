#include <vector>
#include <cstdint>
#include <iostream>

#define ll int64_t

int main() {
  ll N;
  std::cin >> N;
  std::vector<std::vector<int>> mat(N, std::vector<int>(N, 0));
  std::vector<int> colors(N);

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::cin >> mat[i][j];
    }
  }

  ll temp;
  std::cin >> temp;

  for (size_t i = 0; i < N; ++i) {
    std::cin >> colors[i];
  }

  ll ans = 0;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (mat[i][j] == 0) {
        continue;
      }

      if (colors[i] != colors[j]) {
        ++ans;
      }
    }
  }

  std::cout << ans << '\n';

  return 0;
}
