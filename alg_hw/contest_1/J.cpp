#include <iostream>
#include <vector>

size_t bin_search(const std::vector<int> &vec, int target, int right) {
  int left = -1;

  while (left < right - 1) {
    size_t mid = left + (right - left) / 2;

    if (target >= vec[mid]) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return right;
}

size_t count_leq(const std::vector<std::vector<int>> &matrix,
                 const int target) {

  size_t x = matrix.size(), y = matrix[0].size(), ans = 0;
  size_t cur_leq = 0, prev_leq = matrix[0].size();

  for (size_t y = 0; y < matrix.size(); ++y) {
    cur_leq = bin_search(matrix[y], target, prev_leq);
    ans += cur_leq;
    prev_leq = cur_leq;
  }

  return ans;
}

int main() {
  size_t n = 0, k = 0;

  std::cin >> n >> k;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  int left = matrix[0][0];
  int right = matrix[n - 1][n - 1];

  while (left < right - 1) {
    int mid = left + (right - left) / 2;

    if (k > count_leq(matrix, mid)) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  std::cout << left << '\n';

  return 0;
}
