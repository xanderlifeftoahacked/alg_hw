#include <iostream>
#include <vector>

int main() {
  std::string s;
  std::cin >> s;

  std::vector<int> prefix_len(s.size());

  prefix_len[0] = 0;

  for (size_t i = 1; i < prefix_len.size(); ++i) {

    int prev = prefix_len[i - 1];
    while (prev > 0 && s[i] != s[prev]) {
      prev = prefix_len[prev - 1];
    }

    if (s[i] == s[prev]) {
      ++prev;
    }

    prefix_len[i] = prev;
  }

  std::cout << s.size() - prefix_len[s.size() - 1] << '\n';

  return 0;
}
