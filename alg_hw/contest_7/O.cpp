#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstdint>

#define ll int64_t

int main() {
  int N, M;
  std::cin >> N >> M;
  std::vector<std::vector<int>> maze(N, std::vector<int>(M));

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      std::cin >> maze[i][j];
    }
  }

  std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
  std::queue<std::tuple<int, int, int>> q;
  q.push({0, 0, 0});
  visited[0][0] = true;

  std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  while (!q.empty()) {
    int x, y, steps;
    std::tie(x, y, steps) = q.front();
    q.pop();

    for (auto dir : directions) {
      int nx = x, ny = y;
      while (nx + dir.first >= 0 && nx + dir.first < N && ny + dir.second >= 0 && ny + dir.second < M &&
             maze[nx + dir.first][ny + dir.second] != 1) {
        nx += dir.first;
        ny += dir.second;
        if (maze[nx][ny] == 2) {
          std::cout << steps + 1 << '\n';
          return 0;
        }
      }
      if (!visited[nx][ny]) {
        visited[nx][ny] = true;
        q.push({nx, ny, steps + 1});
      }
    }
  }
  return 0;
}
