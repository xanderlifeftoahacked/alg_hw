#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>

int main() {
  size_t n = 0;
  constexpr size_t ascii_size = 256;
  std::array<int, ascii_size> chars_count = {};

  std::cin >> n;
  std::getchar();

  while (n--) {
    ++chars_count[std::getchar()];
  }

  char center = 0;
  bool found_center = false;
  std::string palindrome_half;
  for (size_t i = 0; i < ascii_size; ++i) {
    if (chars_count[i] % 2 != 0 && found_center == false) {
      center = i;
      found_center = true;
    } else {
      size_t ctr = chars_count[i] / 2;
      while (ctr--) {
        palindrome_half += i;
      }
    }
  }
  std::cout << palindrome_half;
  if (found_center) {
    std::cout << center;
  }
  std::reverse(std::begin(palindrome_half), std::end(palindrome_half));
  std::cout << palindrome_half << '\n';

  return 0;
}
