#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> find_bridges(vector<vector<int>> &graph) {
  vector<bool> visited(graph.size(), false);
  vector<int> up(graph.size(), 1e9);
  vector<int> tin(graph.size(), 1e9);
  vector<pair<int, int>> ans;
  int time = 0;

  function<void(int, int)> dfs = [&](int v, int p) {
    visited[v] = true;
    tin[v] = up[v] = ++time;

    for (auto u : graph[v]) {
      if (u == p)
        continue;

      if (!visited[u]) {
        dfs(u, v);
        up[v] = min(up[v], up[u]);
      } else {
        up[v] = min(tin[u], up[v]);
      }
    }

    if (tin[v] == up[v] && p != -1) {
      ans.push_back({max(v, p), min(v, p)});
    }
  };

  for (size_t v = 0; v < graph.size(); ++v) {
    if (!visited[v])
      dfs(v, -1);
  }

  return ans;
}

int main() {
  int n, m;

  cin >> n >> m;
  vector<vector<int>> graph(n, vector<int>());

  map<pair<int, int>, int> streets;

  int a, b;
  for (size_t i = 1; i <= m; ++i) {
    cin >> a >> b;

    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
    streets[{max(a - 1, b - 1), min(a - 1, b - 1)}] = i;
  }

  auto ans = find_bridges(graph);
  cout << ans.size() << '\n';

  set<int> ans_new;
  for (auto [a, b] : ans) {
    ans_new.insert(streets[{a, b}]);
  }

  for (auto elem : ans_new) {
    cout << elem << ' ';
  }
  cout << '\n';

  return 0;
}
