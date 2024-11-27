#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  size_t n = 0, k = 0;

  std::cin >> n >> k;
  std::vector<int> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  int min = std::numeric_limits<int>::max();
  std::deque<std::pair<int, int>> suff_min;
  for (size_t i = k; i > 0; --i) {
    min = std::min(min, arr[i - 1]);
    suff_min.push_front({min, i - 1});
  }

  size_t ptr = 0;
  while (ptr + k - 1 < arr.size()) {
    while (!suff_min.empty() && suff_min.front().second < ptr) {
      suff_min.pop_front();
    }
    while (!suff_min.empty() && suff_min.back().first > arr[ptr + k - 1]) {
      suff_min.pop_back();
    }
    suff_min.push_back({arr[ptr + k - 1], ptr + k - 1});

    std::cout << suff_min.front().first << '\n';
    ++ptr;
  }

  return 0;
}
