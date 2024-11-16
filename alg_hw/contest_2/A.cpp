#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int n = 0, m = 0;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> segments(n);

  for (size_t i = 0; i < n; ++i) {
    std::pair<int, int> segment;
    std::cin >> segment.first >> segment.second;
    segments[i] = segment;
  }

  std::sort(std::begin(segments), std::end(segments),
            [](const auto &lhs, const auto &rhs) { return lhs.second > rhs.second; });

  int point = 0;
  while (m--) {
    int ans = 0;
    std::cin >> point;

    for (size_t i = 0; i < segments.size(); ++i) {
      if (point > segments[i].second)
        break;
      if (point >= segments[i].first)
        ++ans;
    }

    std::cout << ans << ' ';
  }

  std::cout << '\n';
  return 0;
}
