#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define int long long

struct Info {
  int c;
  int f;
  Info() : c{0LL}, f{0LL} {
  }
};

int a, h;
vector<int> find_path(const vector<vector<int>> &graph, map<pair<int, int>, Info> &edges) {
  int cur = a;
  vector<int> ans = {cur};

  while (cur != h) {
    for (auto to : graph[cur]) {
      if (edges[{cur, to}].f > 0) {
        ans.push_back(to);
        --edges[{cur, to}].f;
        cur = to;
        break;
      }
    }
  }

  return ans;
}

int find_max_flow(const vector<vector<int>> &graph, map<pair<int, int>, Info> &edges) {
  vector<bool> visited(graph.size(), false);

  std::function<int(int, int)> dfs = [&](int v, int p) {
    if (v == h)
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

  int out = -1, ans = 0;
  while (out != 0) {
    visited.assign(graph.size(), false);
    out = dfs(a, 1);
    ans += out;
    if (ans >= 2)
      break;
  }

  return ans;
}

signed main() {
  int n, m;
  cin >> n >> m >> a >> h;
  --a, --h;

  vector<vector<int>> graph(n, vector<int>());
  map<pair<int, int>, Info> edges;

  int u, v;
  while (m--) {
    cin >> u >> v;
    --u, --v;

    graph[u].push_back(v);
    graph[v].push_back(u);
    ++edges[{u, v}].c;
    if (!edges.count({v, u}))
      edges[{v, u}] = Info();
  }

  int ans = find_max_flow(graph, edges);

  if (ans < 2) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  auto v1 = find_path(graph, edges);
  auto v2 = find_path(graph, edges);

  for (auto elem : v1) {
    cout << ++elem << ' ';
  }
  cout << '\n';

  for (auto elem : v2) {
    cout << ++elem << ' ';
  }
  cout << '\n';

  return 0;
}
