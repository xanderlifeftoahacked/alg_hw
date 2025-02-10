#include <bits/stdc++.h>

using namespace std;

pair<int, vector<int>> find_css(vector<vector<int>> &graph, vector<vector<int>> &graph_t) {
  vector<bool> visited(graph.size(), false);
  vector<int> order(graph.size());
  vector<int> colors(graph.size(), -1);
  int color = -1;

  function<void(int)> dfs1 = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (!visited[u])
        dfs1(u);
    }
    order.push_back(v);
  };

  function<void(int)> dfs2 = [&](int v) {
    colors[v] = color;
    for (auto u : graph_t[v]) {
      if (colors[u] == -1)
        dfs2(u);
    }
  };

  for (int v = 0; v < graph.size(); ++v) {
    if (!visited[v])
      dfs1(v);
  }

  reverse(order.begin(), order.end());

  for (auto v : order) {
    if (colors[v] == -1) {
      ++color;
      dfs2(v);
    }
  }

  return {color + 1, colors};
}

int main() {
  int n, m;

  cin >> n >> m;

  vector<vector<int>> graph(n, vector<int>());
  vector<pair<int, int>> edges;
  vector<vector<int>> graph_t(n, vector<int>());

  int a, b;
  while (m--) {
    cin >> a >> b;

    graph[--a].push_back(--b);
    graph_t[b].push_back(a);
    edges.push_back({a, b});
  }

  auto [colors_cnt, colors] = find_css(graph, graph_t);
  vector<bool> must_have_station(colors_cnt, true);

  for (auto [from, to] : edges) {
    if (colors[from] != colors[to]) {
      must_have_station[colors[from]] = false;
    }
  }

  set<int> ans;
  for (int c = 0; c < colors_cnt; ++c) {
    if (must_have_station[c] == true) {
      ans.insert(find(colors.begin(), colors.end(), c) - colors.begin() + 1);
    }
  }

  cout << ans.size() << '\n';
  for (auto u : ans) {
    cout << u << '\n';
  }

  return 0;
}
