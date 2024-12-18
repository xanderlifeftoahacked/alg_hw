#include <iostream>
#include <vector>

std::vector<int> z_function(const std::string &s) {
  std::vector<int> z(s.size(), 0);

  z[0] = s.size();
  int left = 0, right = 0;

  for (int i = 1; i < z.size(); ++i) {
    z[i] = std::max(0, std::min(right - i, z[i - left]));

    while (i + z[i] < z.size() && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }

    if (i + z[i] > right) {
      left = i;
      right = i + z[i];
    }
  }

  return z;
};

int main() {
  std::string s, pattern;

  std::cin >> s;
  std::cin >> pattern;

  std::vector<int> z_func = z_function(pattern + "!" + s);
  std::vector<int> ans;

  for (size_t i = pattern.size(); i < z_func.size(); ++i) {
    if (z_func[i] == pattern.size()) {
      ans.push_back(i - pattern.size());
    }
  }

  std::cout << ans.size() << '\n';

  for (const auto elem : ans) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  return 0;
}
