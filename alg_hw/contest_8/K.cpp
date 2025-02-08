#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    return h1 ^ h2;
  }
};

void find_bridges(std::vector<std::vector<int>> &graph, std::unordered_map<std::pair<int, int>, int, pair_hash> &edges,
                  std::unordered_map<std::pair<int, int>, int, pair_hash> &count) {
  std::vector<bool> used(graph.size(), false);
  int timer = 0;
  std::vector<int> tin(graph.size());
  std::vector<int> fup(graph.size());
  std::vector<int> ans;

  std::function<void(int, int)> dfs = [&](int v, int p) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i = 0; i < graph[v].size(); ++i) {
      int to = graph[v][i];
      if (to == p)
        continue;
      if (used[to])
        fup[v] = std::min(fup[v], tin[to]);
      else {
        dfs(to, v);
        fup[v] = std::min(fup[v], fup[to]);
        if (fup[to] > tin[v] && count[{v, to}] < 2)
          ans.push_back(edges[{v, to}]);
      }
    }
  };

  for (int i = 0; i < graph.size(); ++i)
    if (!used[i])
      dfs(i, -1);

  std::cout << ans.size() << '\n';
  std::sort(ans.begin(), ans.end());

  for (auto elem : ans) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  int n, m;
  std::cin >> n >> m;
  auto graph = std::vector<std::vector<int>>(n, std::vector<int>());
  auto edges = std::unordered_map<std::pair<int, int>, int, pair_hash>();
  auto count = std::unordered_map<std::pair<int, int>, int, pair_hash>();

  int a, b;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b;
    edges[{a - 1, b - 1}] = i + 1;
    edges[{b - 1, a - 1}] = i + 1;

    ++count[{a - 1, b - 1}];
    ++count[{b - 1, a - 1}];
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  find_bridges(graph, edges, count);

  return 0;
}
