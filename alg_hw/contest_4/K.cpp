#include <iostream>
#include <string>
#include <cmath>
#include <vector>

size_t count_vert(size_t n) {
  if (n == 0) {
    return 1;
  }
  std::string str = std::to_string(n);
  std::string chars = "0138";
  size_t count = 0, count_small = 0;
  for (auto ch : chars) {
    if (ch - '0' < str[0] - '0') {
      ++count_small;
    }
  }
  count += count_small * std::pow(4, str.size() - 1);
  if (chars.find(str[0]) != std::string::npos && str.size() > 1) {
    count += count_vert(std::stoi(str.substr(1)));
  } else {
    count += count_vert(0);
  }
  return count;
}

size_t count_horizsontal(size_t n) {
  if (n == 0) {
    return 0;
  }
  std::string str = std::to_string(n);
  std::string chars = "0258";
  size_t count = 0, count_small = 0;
  for (auto ch : chars) {
    if (ch - '0' < str[0] - '0') {
      ++count_small;
    }
  }
  count += count_small * std::pow(4, str.size() - 1);
  if (chars.find(str[0]) != std::string::npos && str.size() > 1) {
    count += count_vert(std::stoi(str.substr(1)));
  } else {
    count += count_vert(0);
  }
  return count;
}

int main() {
  size_t l = 0, r = 0;

  std::vector<size_t> horisontal_sim;
  std::cout << count_vert(l) << std::endl;
  std::cin >> l >> r;

  return 0;
}
