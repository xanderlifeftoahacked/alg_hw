#include <bits/stdc++.h>
using namespace std;

void find_css(vector<vector<int>> &graph, vector<vector<int>> &graph1) {
  vector<bool> visited(graph.size(), false);
  vector<int> css(graph.size(), -1);
  vector<int> order;

  function<void(int)> dfs1 = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (visited[u])
        continue;
      dfs1(u);
    }
    order.push_back(v);
  };

  for (size_t v = 0; v < graph.size(); ++v) {
    if (!visited[v])
      dfs1(v);
  }

  reverse(order.begin(), order.end());

  int color = 0;
  function<void(int)> dfs2 = [&](int v) {
    css[v] = color;
    for (auto u : graph1[v]) {
      if (css[u] != -1)
        continue;
      dfs2(u);
    }
  };

  for (auto v : order) {
    if (css[v] == -1) {
      ++color;
      dfs2(v);
    }
  }

  cout << color << '\n';
  for (auto u : css) {
    cout << u << ' ';
  }
  cout << '\n';
}

int main() {
  size_t n, m;
  cin >> n >> m;

  auto graph = vector<vector<int>>(n, vector<int>());
  auto graph1 = vector<vector<int>>(n, vector<int>());

  int a, b;
  for (size_t i = 0; i < m; ++i) {
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph1[b - 1].push_back(a - 1);
  }

  find_css(graph, graph1);

  return 0;
}
