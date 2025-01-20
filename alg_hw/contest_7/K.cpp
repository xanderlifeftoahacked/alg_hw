#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int x1, y1, x2, y2, n;
  std::cin >> n >> x1 >> y1 >> x2 >> y2;

  --x1;
  --x2;
  --y1;
  --y2;

  std::queue<std::pair<int, int>> queue;
  std::vector<std::vector<int>> distances(n, std::vector<int>(n, 0));
  std::vector<std::vector<std::pair<int, int>>> parents(n, std::vector<std::pair<int, int>>(n, {0, 0}));
  std::vector<std::vector<int>> visited(n, std::vector<int>(n, false));

  visited[x1][y1] = true;
  parents[x1][y1] = {-1, -1};
  queue.push({x1, y1});

  std::vector<std::pair<int, int>> delta = {{-2, -1}, {2, 1}, {-2, 1}, {2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

  while (!queue.empty()) {
    auto [cur_x, cur_y] = queue.front();
    queue.pop();
    for (auto [dx, dy] : delta) {
      auto new_x = cur_x + dx;
      auto new_y = cur_y + dy;
      if (new_x < 0 || new_y < 0 || new_x >= n || new_y >= n)
        continue;

      if (visited[new_x][new_y])
        continue;

      visited[new_x][new_y] = true;
      queue.push({new_x, new_y});
      distances[new_x][new_y] = distances[cur_x][cur_y] + 1;
      parents[new_x][new_y] = {cur_x, cur_y};
    }
  }

  std::vector<std::pair<int, int>> ans;
  while (x2 != -1) {
    ans.push_back({x2, y2});
    auto p = parents[x2][y2];
    x2 = p.first;
    y2 = p.second;
  }

  std::cout << ans.size() - 1 << '\n';

  std::reverse(ans.begin(), ans.end());
  for (auto v : ans) {
    std::cout << v.first + 1 << ' ' << v.second + 1 << '\n';
  }
  std::cout << '\n';

  return 0;
}
