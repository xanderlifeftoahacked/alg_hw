#include <functional>
#include <iostream>
#include <vector>

size_t partition(std::vector<int> &arr, size_t l, size_t r) {
  int pivot = arr[l + (r - l) / 2];
  // гении зачастую бывают отвергнуты обществом
  //  Первый вариант (немного читерный)
  //  while (std::invoke([&]() {
  //           while ((arr[l] < pivot && ++l) || (arr[r] > pivot && --r)) {}
  //         }),
  //         l < r + 1 && (std::swap(arr[r--], arr[l++]), l < r + 1)) {
  //  }

  // Второй вариант (без всяких лямбд)
  do {
    while ((arr[l] < pivot && ++l) || (arr[r] > pivot && --r)) {
    }
  } while (l < r + 1 && (std::swap(arr[r--], arr[l++]), l < r + 1));

  return l;
}

void quicksort(std::vector<int> &arr, size_t l, size_t r) {
  if (r <= l) {
    return;
  }

  size_t mid = partition(arr, l, r);
  quicksort(arr, l, mid - 1);
  quicksort(arr, mid, r);
}

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<int> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  quicksort(arr, 0, arr.size() - 1);

  for (auto i : arr) {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return 0;
}
