
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#define ll long long

std::vector<int> dodfs(std::map<int, std::vector<int>> &graph, int v, std::vector<int> &visited) {

  std::vector<int> ans;

  std::function<void(int)> dfs = [&](int u) {
    visited[u] = true;
    for (auto v : graph[u])
      if (!visited[v]) {
        ans.push_back(v);
        dfs(v);
      }
  };

  ans.push_back(v);
  dfs(v);
  return ans;
}

int main() {
  int N, M;

  std::cin >> N >> M;
  std::map<int, std::vector<int>> graph;

  for (size_t i = 0; i < M; ++i) {
    int a, b;
    std::cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  std::vector<int> visited(N, false);

  std::vector<std::vector<int>> ans;
  for (int v = 0; v < visited.size(); ++v) {
    std::vector<int> temp;
    if (!visited[v]) {
      temp = dodfs(graph, v, visited);
    }
    if (temp.size() == 0) {
      continue;
    }
    ans.push_back(temp);
  }

  std::cout << ans.size() << '\n';

  for (auto comp : ans) {
    std::cout << comp.size() << '\n';
    for (auto v : comp) {
      std::cout << v + 1 << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
