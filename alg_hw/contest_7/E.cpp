#include <functional>
#include <iostream>
#include <map>
#include <vector>

#define ll long long

int dodfs(std::map<int, std::vector<int>> graph, int s) {
  std::vector<bool> visited(graph.size(), false);
  size_t ans = 1;

  std::function<void(int)> dfs = [&](int u) {
    visited[u] = true;
    for (auto v : graph[u])
      if (!visited[v]) {
        ++ans;
        dfs(v);
      }
  };

  dfs(s);

  return ans;
}

int main() {
  int N, S;

  std::cin >> N >> S;
  std::map<int, std::vector<int>> graph;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      int temp = 0;
      std::cin >> temp;
      if (temp) {
        graph[i].push_back(j);
      }
    }
  }

  std::cout << dodfs(graph, S - 1) << '\n';

  return 0;
}
