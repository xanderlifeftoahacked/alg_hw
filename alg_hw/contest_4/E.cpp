#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector<uint64_t> seq_x(n);
  std::vector<uint64_t> seq_y(n);
  std::vector<uint64_t> seq_z(n);

  seq_x[0] = 1;
  seq_y[0] = 1;
  seq_z[0] = 1;

  for (size_t i = 1; i < n; ++i) {
    seq_x[i] = seq_x[i - 1] + seq_y[i - 1] + seq_z[i - 1];
    seq_y[i] = seq_x[i];
    seq_z[i] = seq_x[i - 1] + seq_y[i - 1];
  }

  std::cout << seq_x[n - 1] + seq_y[n - 1] + seq_z[n - 1] << '\n';

  return 0;
}
