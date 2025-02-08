#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void do_dfs(std::unordered_map<int, std::vector<int>> &graph, int n) {
  std::vector<int> visited(n, 0);

  bool bad = false;
  std::function<void(int)> dfs = [&](int v) {
    if (visited[v] == 2) {
      return;
    }
    if (visited[v] == 1) {
      bad = true;
      return;
    }
    visited[v] = 1;
    for (auto u : graph[v]) {
      dfs(u);
      if (bad)
        return;
    }
    visited[v] = 2;
  };

  for (int i = 0; i < n; ++i) {
    if (visited[i] == 0) {
      dfs(i);
      if (bad)
        break;
    }
  }

  if (bad) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
  }
}

int main() {
  int n;
  std::cin >> n;

  std::unordered_map<int, std::vector<int>> graph;
  for (int i = 0; i < n - 1; ++i) {
    std::string colors;
    int j = i + 1;
    std::cin >> colors;
    while (j - i - 1 < colors.size()) {
      char color = colors[j - i - 1];
      if (color == 'R') {
        graph[i].push_back(j);
      } else {
        graph[j].push_back(i);
      }
      ++j;
    }
  }
  do_dfs(graph, n);

  return 0;
}
