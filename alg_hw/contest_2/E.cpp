#include <iostream>
#include <set>
#include <string>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::cin.ignore();

  auto cmp = [](const std::string &lhs, const std::string &rhs) {
    return lhs.size() < rhs.size();
  };

  std::multiset<std::string, decltype(cmp)> words(cmp);

  std::string temp;
  while (n--) {
    std::getline(std::cin, temp);
    words.insert(temp);
  }

  for (const auto &word : words) {
    std::cout << word << '\n';
  }

  return 0;
}
