#include <iostream>
#include <vector>

int main() {
  size_t n = 0, k = 0;
  std::cin >> n;
  std::vector<int> buttons(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> buttons[i];
  }

  std::cin >> k;

  size_t temp = 0;
  while (k--) {
    std::cin >> temp;
    --buttons[temp - 1];
  }

  for (const int i : buttons) {
    if (i < 0) {
      std::cout << "yes\n";
    } else {
      std::cout << "no\n";
    }
  }

  return 0;
}
