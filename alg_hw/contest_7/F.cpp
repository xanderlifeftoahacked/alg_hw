#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

std::vector<int> dodfs(const std::map<int, std::vector<int>> &graph, size_t m) {
  std::vector<bool>visited(m, false);
  std::vector<int> answer;

  std::function<void(int)> dfs = [&](int u) {
    visited[u] = true;
    answer.push_back(u);

    for (const auto v : graph.at(u)) {
      if (!visited[v]) {
        dfs(v);
      }
    }
  };

  dfs(1);
  return answer;
}

int main() {
  size_t n, m = 0;
  std::cin >> n >> m;

  if (m == 0) {
    std::cout << "1\n1\n";
    return 0;
  }

  std::map<int, std::vector<int>> graph;

  for (size_t i = 0; i < n; ++i) {
    graph[i] = std::vector<int>();
  }

  int x, y = 0;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  std::vector<int> ans = dodfs(graph, m);
  std::sort(ans.begin(), ans.end());

  std::cout << ans.size() << '\n';
  for (const auto i : ans) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  return 0;
}
