#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, long long> streets;
map<pair<int, int>, int> egde_cnt;
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
    if (tin[v] == up[v] && p != -1 && egde_cnt[{max(v, p), min(v, p)}] == 1) {
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
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m;

  cin >> n >> m;
  vector<vector<int>> graph(n, vector<int>());

  long long a, b, id;
  for (size_t i = 1; i <= m; ++i) {
    cin >> id >> a >> b;

    graph[a].push_back(b);
    graph[b].push_back(a);
    streets[{max(a, b), min(a, b)}] = id;
    ++egde_cnt[{max(a, b), min(a, b)}];
  }

  auto ans = find_bridges(graph);

  set<int> ans_new;
  for (auto [a, b] : ans) {
    ans_new.insert(streets[{a, b}]);
  }

  if (ans_new.size() == 0) {
    cout << "-1\n";
    return 0;
  }

  for (auto elem : ans_new) {
    cout << elem << ' ';
  }
  cout << '\n';

  return 0;
}
