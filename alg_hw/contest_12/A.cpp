#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define int long long

struct Info {
  int c;
  int f;
};

int find_max_flow(const vector<vector<int>> &graph, map<pair<int, int>, Info> &edges) {
  vector<bool> visited(graph.size(), false);
  int t = graph.size() - 1;

  std::function<int(int, int)> dfs = [&](int v, int p) {
    if (v == t)
      return p;
    if (visited[v])
      return 0LL;

    visited[v] = true;

    for (auto u : graph[v]) {
      if (edges[{v, u}].c > edges[{v, u}].f) {
        int delta = dfs(u, min(p, edges[{v, u}].c - edges[{v, u}].f));
        if (delta > 0) {
          edges[{v, u}].f += delta;
          edges[{u, v}].f -= delta;
          return delta;
        }
      }
    }

    return 0LL;
  };

  int out = -1, ans = dfs(0, LLONG_MAX);
  while (out != 0) {
    visited.assign(graph.size(), false);
    out = dfs(0, LLONG_MAX);
    ans += out;
  }

  return ans;
}

signed main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n, vector<int>());
  map<pair<int, int>, Info> edges;

  int a, b, c;
  while (m--) {
    cin >> a >> b >> c;
    --a, --b;

    graph[a].push_back(b);
    graph[b].push_back(a);
    edges[{a, b}] = {c, 0};
    if (!edges.count({b, a}))
      edges[{b, a}] = {0, 0};
  }

  int ans = find_max_flow(graph, edges);
  cout << ans << '\n';

  return 0;
}
