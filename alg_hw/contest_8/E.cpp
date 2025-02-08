#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

std::vector<int> top_sort(std::vector<std::vector<int>>& graph) {
  std::vector<int> visited(graph.size(), -1);
  std::vector<int> ans;

  std::function<bool(int)> dfs = [&](int v) {
    visited[v] = 0;
    for (auto u : graph[v]) {
      if (visited[u] == 0)
        return false;

      if (visited[u] == -1)
        dfs(u);
    }
    visited[v] = 1;
    ans.push_back(v);
    return true;
  };

  for (int i = 0; i < graph.size(); ++i) {
    if (visited[i] == -1) {
      bool is_good = dfs(i);
      if (!is_good) {
        std::cout << "No\n";
        return {};
      }
    }
  }

  std::reverse(std::begin(ans), std::end(ans));

  return ans;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  auto graph = std::vector<std::vector<int>>(n);

  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
  }

  auto res = top_sort(graph);

  if (res.size()) {
    for (auto elem : res) {
      std::cout << elem + 1 << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
