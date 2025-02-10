#include <bits/stdc++.h>

using namespace std;

set<int> find_cutpoints(vector<vector<int>> &graph) {
  vector<bool> visited(graph.size(), false);
  vector<int> tin(graph.size());
  vector<int> up(graph.size());
  set<int> ans;
  int time = 0;

  function<void(int, int)> dfs = [&](int v, int p) {
    visited[v] = true;
    int child_cnt = 0;
    tin[v] = up[v] = ++time;

    for (auto u : graph[v]) {
      if (v == p) {
        continue;
      }
      if (!visited[u]) {
        ++child_cnt;
        dfs(u, v);
        up[v] = min(up[u], up[v]);

        if (up[u] >= tin[v] && p != -1) {
          ans.insert(v);
        }
      } else {
        up[v] = min(tin[u], up[v]);
      }
    }

    if (p == -1 && child_cnt > 1) {
      ans.insert(v);
    }
  };

  dfs(0, -1);

  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n, vector<int>());

  int a, b;
  while (m--) {
    cin >> a >> b;
    graph[--a].push_back(--b);
    graph[b].push_back(a);
  }

  auto ans = find_cutpoints(graph);
  cout << ans.size() << '\n';
  for (auto v : ans) {
    cout << v + 1 << ' ';
  }
  cout << '\n';

  return 0;
}
