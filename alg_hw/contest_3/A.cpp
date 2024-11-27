#include <iostream>
#include <vector>

void heapify(std::vector<int> &arr, size_t idx_root, size_t n) {
  size_t idx_max = idx_root;
  size_t idx_left = 2 * idx_root + 1;
  size_t idx_right = 2 * idx_root + 2;

  if (idx_left < n && arr[idx_left] > arr[idx_max]) {
    idx_max = idx_left;
  }

  if (idx_right < n && arr[idx_right] > arr[idx_max]) {
    idx_max = idx_right;
  }

  if (idx_root != idx_max) {
    std::swap(arr[idx_root], arr[idx_max]);
    heapify(arr, idx_max, n);
  }
}

void heap_sort(std::vector<int> &arr) {
  for (size_t i = arr.size() / 2; i > 0; --i) {
    heapify(arr, i - 1, arr.size());
  }

  for (size_t i = arr.size(); i > 0; --i) {
    std::swap(arr[0], arr[i - 1]);
    heapify(arr, 0, i - 1);
  }
}

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<int> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  heap_sort(arr);

  for (const auto i : arr) {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return 0;
}
