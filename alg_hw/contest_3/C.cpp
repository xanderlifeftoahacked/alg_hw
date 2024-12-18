#include <iomanip>
#include <iostream>
#include <vector>

double find_med(const std::vector<double>& seq1, const std::vector<double>& seq2) {
  int l = -1;
  int r = seq1.size();

  while (l + 1 < r) {
    int m = l + (r - l) / 2;

    if (seq1[m - 1] >= seq2[seq1.size() - m]) {
      r = m;
    } else {
      l = m;
    }
  }
  --l;
  --r;

  return (std::max(seq1[l], seq2[seq1.size() - r - 1]) + std::min(seq1[r], seq2[seq1.size() - l - 1])) / 2.f;
}

int main() {
  size_t n = 0, m = 0;
  std::cout << std::fixed << std::setprecision(5);

  std::cin >> n >> m;

  std::vector<std::vector<double>> sequences(n, std::vector<double>(m, 0));

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
