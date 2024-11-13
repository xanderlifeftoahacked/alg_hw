#include <algorithm>
#include <iostream>

int main() {
  int a = 0, b = 0, c = 0;
  std::cin >> a >> b >> c;

  int full_cycles = std::min({a, b / 2, c});
  int total_time = full_cycles * 4;

  a -= full_cycles;
  b -= full_cycles * 2;
  c -= full_cycles;

  if (a > 0) {
    total_time++;
    if (b > 0) {
      total_time++;
      b--;
      if (c > 0) {
        total_time++;
        if (b > 0) {
          total_time++;
        }
      }
    }
  }

  std::cout << total_time << '\n';

  return 0;
}
