#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::unordered_map<int, std::vector<int>> graph;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      int temp;
      std::cin >> temp;
      if (temp) {
        graph[i].push_back(j);
      }
    }
  }

  std::vector<bool> visited(n, false);
  std::vector<int> path;
  std::vector<int> cycle;

  std::function<bool(int, int)> dfs = [&](int node, int parent) {
    visited[node] = true;
    path.push_back(node);

    for (auto neighbor : graph[node]) {
      if (!visited[neighbor]) {
        if (dfs(neighbor, node)) {
          return true;
        }
      } else if (neighbor != parent) {
        cycle.push_back(neighbor);
        for (int i = path.size() - 1; i >= 0; --i) {
          cycle.push_back(path[i]);
          if (path[i] == neighbor)
            break;
        }
        return true;
      }
    }

    path.pop_back();
    return false;
  };

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      if (dfs(i, -1)) {
        std::cout << "YES" << '\n';
        cycle.pop_back();
        std::cout << cycle.size() << '\n';
        for (int v : cycle) {
          std::cout << v + 1 << ' ';
        }
        std::cout << '\n';
        return 0;
      }
    }
  }

  std::cout << "NO" << '\n';
  return 0;
}
