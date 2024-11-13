#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int32_t> array(n, 0);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  int32_t target = 0;
  std::cin >> target;

  int32_t left = 0, right = n - 1;

  int32_t ans = -1;
  while (left <= right) {
    int32_t mid = left + (right - left) / 2;

    if (array[mid] == target) {
      std::cout << mid << '\n';
      return 0;
    }

    if (array[left] <= array[mid]) {
      if (array[left] <= target && array[mid] >= target) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    } else {
      if (array[mid] <= target && array[right] >= target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }

  std::cout << "-1\n";

  return 0;
}
