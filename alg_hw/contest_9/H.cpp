#include <bits/stdc++.h>
using namespace std;

vector<string> names;

map<int, set<string>> find_css(vector<vector<int>> &graph, vector<vector<int>> &graph_t) {
  vector<bool> visited(graph.size(), false);
  vector<int> colors(graph.size(), -1);
  int color = -1;
  vector<int> order;
  map<int, set<string>> ans;

  function<void(int)> dfs = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (!visited[u])
        dfs(u);
    }
    order.push_back(v);
  };

  function<void(int)> dfs1 = [&](int v) {
    colors[v] = color;
    for (auto u : graph_t[v]) {
      if (colors[u] == -1)
        dfs1(u);
    }
  };

  for (size_t v = 0; v < graph.size(); ++v) {
    if (!visited[v])
      dfs(v);
  }

  reverse(order.begin(), order.end());

  for (auto u : order) {
    if (colors[u] == -1) {
      ++color;
      dfs1(u);
    }
  }

  for (int v = 0; v < graph.size(); ++v) {
    ans[colors[v]].insert(names[v]);
  }

  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;

  names.resize(n);

  int id;
  string name;
  for (int i = 0; i < n; ++i) {
    cin >> id;
    cin.ignore();
    getline(cin, name);
    names[id] = name;
  }

  vector<vector<int>> graph(n, vector<int>());
  vector<vector<int>> graph_t(n, vector<int>());

  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph_t[b].push_back(a);
  }

  auto css = find_css(graph, graph_t);

  vector<pair<int, set<string>>> sorted_css(css.begin(), css.end());

  sort(sorted_css.begin(), sorted_css.end(), [](const pair<int, set<string>> &a, const pair<int, set<string>> &b) {
    return *a.second.begin() < *b.second.begin();
  });

  for (auto &[id, names_set] : sorted_css) {
    for (auto &name : names_set) {
      cout << name << '\n';
    }
    cout << '\n';
  }

  return 0;
}
