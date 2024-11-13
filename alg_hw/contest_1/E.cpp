#include <array>
#include <cstdint>
#include <iostream>

int main() {
  constexpr uint8_t int_size = sizeof(uint16_t) * 8;
  size_t n = 0;
  std::cin >> n;
  std::array<uint8_t, int_size> accumulator = {};

  uint32_t cur = 0;
  while (n--) {
    std::cin >> cur;

    for (size_t i = 0; i < int_size; ++i) {
      accumulator[accumulator.size() - i - 1] += (cur & 1);
      accumulator[accumulator.size() - i - 1] %= 3;
      cur >>= 1;
    }
  }

  uint16_t ans = 0;
  char meet_times = '1';
  for (size_t i = 0; i < int_size; ++i) {
    if (accumulator[i] == 2) {
      meet_times = '2';
      ans += (accumulator[i] - 1) * (1 << (int_size - i - 1));
    } else {
      ans += (accumulator[i]) * (1 << (int_size - i - 1));
    }
  }

  std::cout << ans << ' ' << meet_times << '\n';

  return 0;
}
