#include <iostream>
#include <limits>

int main() {
  int ans = 0, cur = 0, prev = std::numeric_limits<int>::max();

  while (std::cin >> cur) {
    if (cur == 0) {
      break;
    }
    if (cur > prev) {
      ++ans;
    }

    prev = cur;
  }

  std::cout << ans << '\n';

  return 0;
}
