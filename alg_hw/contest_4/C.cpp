#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<uint64_t> paths(n + 1);
  paths[1] = 0;

  for (size_t i = 2; i < n + 1; ++i) {
    uint64_t min = paths[i - 1];
    if (i % 2 == 0) {
      min = std::min(min, paths[i / 2]);
    }
    if (i % 3 == 0) {
      min = std::min(min, paths[i / 3]);
    }
    paths[i] = min + 1;
  }

  std::cout << paths[n] << '\n';

  std::vector<uint64_t> path(1);
  path[0] = n;
  uint64_t i = n;
  while (i != 1) {
    uint64_t minimum = paths[i - 1];
    if (i % 2 == 0) {
      minimum = std::min(minimum, paths[i / 2]);
    }
    if (i % 3 == 0) {
      minimum = std::min(minimum, paths[i / 3]);
    }

    if (minimum == paths[i - 1]) {
      --i;
    } else if (i % 2 == 0 && minimum == paths[i / 2]) {
      i /= 2;
    } else if (i % 3 == 0) {
      i /= 3;
    }

    path.push_back(i);
  }

  for (size_t i = path.size(); i > 0; --i) {
    std::cout << path[i - 1] << ' ';
  }

  std::cout << '\n';

  return 0;
}
