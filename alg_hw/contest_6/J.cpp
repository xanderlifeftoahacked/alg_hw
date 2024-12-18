#include <algorithm>
#include <iostream>
#include <vector>

void count_sort(std::vector<int> &arr, int exp) {
  int n = arr.size();
  std::vector<int> output(n);
  int count[10] = {0};

  for (int i = 0; i < n; ++i) {
    ++count[(arr[i] / exp) % 10];
  }

  for (int i = 1; i < 10; ++i) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; --i) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    --count[(arr[i] / exp) % 10];
  }

  for (int i = 0; i < n; ++i) {
    arr[i] = output[i];
  }
}

void radix_sort(std::vector<int> &arr) {
  int max_val = *std::max_element(arr.begin(), arr.end());
  for (size_t exp = 1; max_val / exp > 0; exp *= 10) {
    count_sort(arr, exp);
  }
}

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  radix_sort(arr);

  for (size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';

  return 0;
}
