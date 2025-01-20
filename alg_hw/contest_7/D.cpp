#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;
  std::vector<std::vector<int>> mat(N, std::vector<int>(N, 0));

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::cin >> mat[i][j];
    }
  }

  int ans = 0;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (mat[i][j] == 0) {
        continue;
      }
      ++ans;
    }
  }

  std::cout << ans << '\n';

  return 0;
}
