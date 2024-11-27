#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<int> steps(n + 1);

  steps[0] = 1;

  for (size_t i = 1; i < n + 1; ++i) {
    steps[i] = steps[i - 1];

    if (i >= 2) {
      steps[i] += steps[i - 2];
    }

    if (i >= 3) {
      steps[i] += steps[i - 3];
    }
  }

  std::cout << steps[n] << '\n';

  return 0;
}
