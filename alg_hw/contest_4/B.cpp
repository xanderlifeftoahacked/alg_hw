#include <vector>
#include <iostream>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int> seq(n + 1);

  seq[0] = 1;
  seq[1] = 1;

  for (size_t i = 2; i < n + 1; ++i) {
    if (i % 2) {
      seq[i] = seq[(i - 1) / 2 + 1] + seq[(i - 1) / 2] + 1;
    } else {
      seq[i] = seq[i / 2] + 1;
    }
  }

  std::cout << seq[n] << '\n';

  return 0;
}
