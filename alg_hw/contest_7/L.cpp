#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n = 8;
  std::string first, second;
  std::cin >> first >> second;
  int x1 = first[0] - 97;
  int y1 = first[1] - 49;

  int x2 = second[0] - 97;
  int y2 = second[1] - 49;

  if ((x1 % 2 + y1 % 2) % 2 != (x2 % 2 + y2 % 2) % 2) {
    std::cout << "-1\n";
    return 0;
  }

  std::queue<std::pair<int, int>> queue;
  std::vector<std::vector<int>> distances1(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> distances2(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> visited(n, std::vector<int>(n, false));

  std::vector<std::pair<int, int>> delta = {{-2, -1}, {2, 1}, {-2, 1}, {2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

  visited[x1][y1] = true;
  queue.push({x1, y1});
  auto bfs = [&](std::vector<std::vector<int>> &distances) {
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
      }
    }
  };

  bfs(distances1);
  visited = std::vector<std::vector<int>>(n, std::vector<int>(n, false));
  visited[x2][y2] = true;
  queue.push({x2, y2});
  bfs(distances2);

  int min_dist = 1e8;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (distances1[i][j] == distances2[i][j]) {
        min_dist = std::min(min_dist, distances1[i][j]);
      }
    }
  }
  std::cout << min_dist << '\n';

  return 0;
}
