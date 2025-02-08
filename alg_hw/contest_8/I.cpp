#include <iostream>
#include <vector>
#include <tuple>

void dfs(int u, std::vector<std::vector<int>>& g, std::vector<bool>& visited, std::vector<int>& order) {
  visited[u] = true;
  for (int v : g[u]) {
    if (!visited[v]) {
      dfs(v, g, visited, order);
    }
  }
  order.push_back(u);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::tuple<int, int, int, int>> trains(n);
  for (int i = 0; i < n; ++i) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    trains[i] = std::make_tuple(a, b, c, d);
  }
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    auto [a1, b1, c1, d1] = trains[i];
    for (int j = i + 1; j < n; ++j) {
      auto [a2, b2, c2, d2] = trains[j];
      int s_start = std::max(a1, a2);
      int s_end = std::min(b1, b2);
      if (s_start > s_end) {
        std::cout << i << " " << j << std::endl;
        continue;
      }
      int64_t ti = c1 + (s_start - a1) * 1LL * d1;
      int64_t tj = c2 + (s_start - a2) * 1LL * d2;
      if (ti < tj) {
        g[i].push_back(j);
      } else if (tj < ti) {
        g[j].push_back(i);
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    std::cout << i << ": ";
    for (auto elem : g[i]) {
      std::cout << elem << ' ';
    }
    std::cout << std::endl;
  }
  std::vector<bool> visited(n, false);
  std::vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i, g, visited, order);
    }
  }
  for (int i = order.size() - 1; i >= 0; --i) {
    std::cout << order[i] + 1 << " ";
  }
  std::cout << '\n';
  return 0;
}
