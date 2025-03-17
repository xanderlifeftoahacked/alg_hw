#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> new_edges;

set<pair<int, int>> reduction(int n) {
  vector<vector<int>> graph(n);
  for (const auto &[u, v] : new_edges) {
    graph[u].push_back(v);
  }

  vector<int> in_degree(n, 0);
  for (int u = 0; u < n; ++u) {
    for (int v : graph[u]) {
      in_degree[v]++;
    }
  }

  vector<bool> visited(n, false);
  vector<int> order;
  function<void(int)> dfs = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (!visited[u])
        dfs(u);
    }
    order.push_back(v);
  };

  for (int v = 0; v < n; ++v) {
    if (!visited[v])
      dfs(v);
  }

  reverse(order.begin(), order.end());
  vector<vector<bool>> closure(n, vector<bool>(n, false));
  for (auto u : order) {
    closure[u][u] = true;
    for (auto v : graph[u]) {
      closure[u][v] = true;
      for (int w = 0; w < n; ++w) {
        if (closure[v][w]) {
          closure[u][w] = true;
        }
      }
    }
  }

  set<pair<int, int>> result;
  for (const auto &[u, v] : new_edges) {
    bool bad = false;
    for (int w : graph[u]) {
      if (w == v)
        continue;
      if (closure[w][v]) {
        bad = true;
        break;
      }
    }
    if (!bad) {
      result.insert({u, v});
    }
  }

  return result;
}

void find_css(vector<vector<int>> &graph, vector<vector<int>> &graph1) {
  int n = graph.size();
  vector<bool> visited(n, false);
  vector<int> css(n, -1);
  map<int, vector<int>> components;
  vector<int> order;

  function<void(int)> dfs1 = [&](int v) {
    visited[v] = true;
    for (int u : graph[v]) {
      if (!visited[u]) {
        dfs1(u);
      }
    }
    order.push_back(v);
  };

  for (int v = 0; v < n; ++v) {
    if (!visited[v]) {
      dfs1(v);
    }
  }

  reverse(order.begin(), order.end());
  int color = 0;

  function<void(int, int)> dfs2 = [&](int v, int c) {
    css[v] = c;
    for (int u : graph1[v]) {
      if (css[u] == -1) {
        dfs2(u, c);
      }
    }
  };

  for (int v : order) {
    if (css[v] == -1) {
      dfs2(v, color);
      color++;
    }
  }

  for (int v = 0; v < n; ++v) {
    components[css[v]].push_back(v);
  }

  for (int v = 0; v < n; ++v) {
    for (int to : graph[v]) {
      if (css[v] != css[to]) {
        new_edges.push_back({v, to});
      }
    }
  }

  for (const auto &[key, comp] : components) {
    if (comp.size() < 2)
      continue;
    for (size_t i = 0; i < comp.size(); ++i) {
      int current = comp[i];
      int next = comp[(i + 1) % comp.size()];
      new_edges.emplace_back(current, next);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n);
  vector<vector<int>> graph1(n);

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph1[b].push_back(a);
  }

  new_edges.clear();
  find_css(graph, graph1);
  auto ans = reduction(n);

  cout << ans.size() << '\n';
  for (auto [u, v] : ans) {
    cout << u + 1 << ' ' << v + 1 << '\n';
  }

  return 0;
}
