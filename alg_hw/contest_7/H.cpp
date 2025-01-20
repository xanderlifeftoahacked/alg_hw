#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
#include <vector>

void bfs(std::vector<std::vector<int>> &matrix, std::pair<int, int> v, std::vector<std::vector<int>> &dist) {
  std::queue<std::pair<int, int>> queue;
  std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));

  visited[v.first][v.second] = true;
  dist[v.first][v.second] = 0;
  queue.push(v);
  std::vector<std::pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

  while (!queue.empty()) {
    auto [cur_x, cur_y] = queue.front();
    queue.pop();

    for (auto [dx, dy] : dirs) {
      auto new_x = cur_x + dx;
      auto new_y = cur_y + dy;

      if (new_x < 0 || new_x >= matrix.size() || new_y < 0 || new_y >= matrix[0].size())
        continue;

      if (visited[new_x][new_y])
        continue;

      visited[new_x][new_y] = true;
      queue.push({new_x, new_y});
      dist[new_x][new_y] = std::min(dist[cur_x][cur_y] + 1, dist[new_x][new_y]);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::queue<std::pair<int, int>> queue;
  std::vector<std::vector<int>> distances(n, std::vector<int>(m, 1e9));
  std::vector<std::vector<int>> mat(n, std::vector<int>(m, 1e9));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> mat[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == 1) {
        bfs(mat, {i, j}, distances);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << distances[i][j] << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
