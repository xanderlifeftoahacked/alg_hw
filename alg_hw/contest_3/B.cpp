#include <iostream>
#include <utility>
#include <vector>

template <typename T>
concept Comparable = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
};

template <Comparable T> class Heap {
  std::vector<T> arr;

  void heapify(size_t idx_root) {
    size_t idx_max = idx_root;
    size_t idx_left = 2 * idx_root + 1;
    size_t idx_right = 2 * idx_root + 2;

    if (idx_left < arr.size() && arr[idx_left] > arr[idx_max]) {
      idx_max = idx_left;
    }

    if (idx_right < arr.size() && arr[idx_right] > arr[idx_max]) {
      idx_max = idx_right;
    }

    if (idx_root != idx_max) {
      std::swap(arr[idx_root], arr[idx_max]);
      heapify(idx_max);
    }
  }

  void sieve(size_t child) {
    if (child <= 0) {
      return;
    }
    size_t parent = (child - 1) / 2;
    if (arr[child] > arr[parent]) {
      std::swap(arr[child], arr[parent]);
      sieve(parent);
    }
  }

public:
  Heap() : arr() {};
  void insert(T val) {
    arr.push_back(val);
    sieve(arr.size() - 1);
  }

  T extract() {
    T temp = arr[0];
    std::swap(arr[0], arr.back());
    arr.pop_back();
    heapify(0);
    return temp;
  }
};

int main() {
  size_t n = 0;
  std::cin >> n;

  Heap<int> heap;
  char command = ' ';
  int val = 0;
  while (n--) {
    std::cin >> command;

    if (command == '0') {
      std::cin >> val;
      heap.insert(val);
    } else if (command == '1') {
      std::cout << heap.extract() << '\n';
    }
  }

  return 0;
}
