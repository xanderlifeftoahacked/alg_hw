#include <iostream>
#include <vector>

#define ll long long

int main() {
  int N = 0;
  std::cin >> N;
  std::vector<std::vector<int>> mat(N, std::vector<int>(N, 0));

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::cin >> mat[i][j];
    }
  }

  ll min_s = 1e10;
  ll ii, jj, kk;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      for (size_t k = 0; k < N; ++k) {
        if (k == j || k == i) {
          continue;
        }
        int s = mat[i][j] + mat[j][k] + mat[k][i];
        if (s < min_s) {
          ii = i;
          kk = k;
          jj = j;
          min_s = s;
        }
      }
    }
  }

  std::cout << ii + 1 << ' ' << jj + 1 << ' ' << kk + 1 << '\n';

  return 0;
}
