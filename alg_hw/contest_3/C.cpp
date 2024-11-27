#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

double find_med(const std::vector<int> &seq1, const std::vector<int> &seq2) {}

int main() {
  std::cout << std::fixed << std::setprecision(5);

  size_t n = 0, m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> sequences(n, std::vector<int>(m, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> sequences[i][j];
    }
  }

  for (size_t first = 0; first < n; ++first) {
    for (size_t second = first + 1; second < n; ++second) {
      std::cout << find_med(sequences[first], sequences[second]) << '\n';
    }
  }

  return 0;
}
