#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

struct Pos {
  int y;
  int x;
  int dir;

  Pos(int _y, int _x, int _dir) : x{_x}, y{_y}, dir{_dir} {
  }
};

int main() {
  int r, c;
  std::cin >> r >> c;

  std::vector<std::string> maze(r);

  std::pair<int, int> start;
  std::pair<int, int> end;
  std::getline(std::cin, maze[0]);
  for (size_t i = 0; i < r; ++i) {
    std::getline(std::cin, maze[i]);
  }

  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < c; ++j) {
      if (maze[i][j] == 'S')
        start = {i, j};
    }
  }

  auto dist = std::vector<std::vector<std::vector<int>>>(r, std::vector<std::vector<int>>(c, std::vector<int>(4, -1)));
  std::queue<Pos> queue;

  // 0 - вправо, 1 - вниз, 2 - влево, 3 - вверх
  for (int i = 0; i < 4; ++i) {
    queue.push(Pos(start.first, start.second, i));
    dist[start.first][start.second][i] = 0;
  }

  while (!queue.empty()) {
    auto cur = queue.front();
    queue.pop();

    if (maze[cur.y][cur.x] == 'F') {
      std::cout << dist[cur.y][cur.x][cur.dir] << '\n';
      return 0;
    }

    int new_dir = (cur.dir + 1) % 4;
    int new_x = cur.x, new_y = cur.y;
    if (new_dir == 0) {
      new_x = cur.x + 1;
    } else if (new_dir == 1) {
      new_y = cur.y + 1;
    } else if (new_dir == 2) {
      new_x = cur.x - 1;
    } else {
      new_y = cur.y - 1;
    }

    if (new_x >= 0 && new_x < c && new_y >= 0 && new_y < r && maze[new_y][new_x] != 'X') {
      if (dist[new_y][new_x][new_dir] == -1) {
        dist[new_y][new_x][new_dir] = dist[cur.y][cur.x][cur.dir] + 1;
        queue.push(Pos(new_y, new_x, new_dir));
      }
    }

    new_x = cur.x;
    new_y = cur.y;
    if (cur.dir == 0) {
      new_x = cur.x + 1;
    } else if (cur.dir == 1) {
      new_y = cur.y + 1;
    } else if (cur.dir == 2) {
      new_x = cur.x - 1;
    } else {
      new_y = cur.y - 1;
    }

    if (new_x >= 0 && new_x < c && new_y >= 0 && new_y < r && maze[new_y][new_x] != 'X') {
      if (dist[new_y][new_x][cur.dir] == -1) {
        dist[new_y][new_x][cur.dir] = dist[cur.y][cur.x][cur.dir] + 1;
        queue.push(Pos(new_y, new_x, cur.dir));
      }
    }
  }

  return 0;
}
