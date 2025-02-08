
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

void do_dfs(std::unordered_map<int, std::vector<int>> &graph, int m) {
  std::vector<int> visited(m, 0);

  bool bad = false;
  std::function<void(int, int)> dfs = [&](int v, int color) {
    visited[v] = color;
    for (auto u : graph[v]) {
      if (visited[u] == 3 - color) {
        continue;
      }
      if (visited[u] == color) {
        bad = true;
        return;
      }
      visited[u] = 3 - color;
      dfs(u, 3 - color);
    }
  };

  for (size_t i = 0; i < m; ++i) {
    if (visited[i] == 0) {
      dfs(i, 1);
    }
  }

  if (bad) {
    std::cout << "NO\n";
    return;
  }

  std::cout << "YES\n";
  std::set<int> ans1;
  std::set<int> ans2;
  for (size_t i = 0; i < visited.size(); ++i) {
    if (visited[i] == 1) {
      ans1.insert(i + 1);
    } else {
      ans2.insert(i + 1);
    }
  }

  if (ans1.size() > ans2.size()) {
    ans1 = std::move(ans2);
  }
  std::cout << ans1.size() << '\n';

  for (auto elem : ans1) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  int n, m;

  std::unordered_map<int, std::vector<int>> examens;
  std::cin >> n >> m;

  int max = 0;
  for (size_t i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    examens[a - 1].push_back(b - 1);
    examens[b - 1].push_back(a - 1);
  }

  do_dfs(examens, n);

  return 0;
}
