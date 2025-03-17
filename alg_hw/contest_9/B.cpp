#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph, graph_t;
vector<bool> visited;
vector<int> order, component;

void dfs1(int v) {
  visited[v] = true;
  for (int u : graph[v]) {
    if (!visited[u]) {
      dfs1(u);
    }
  }
  order.push_back(v);
}

void dfs2(int v, int label) {
  component[v] = label;
  for (int u : graph_t[v]) {
    if (component[u] == -1) {
      dfs2(u, label);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  graph.resize(n);
  graph_t.resize(n);
  vector<pair<int, int>> original_edges;

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    graph[--a].push_back(--b);
    graph_t[b].push_back(a);
    original_edges.emplace_back(a, b);
  }

  component.assign(n, -1);
  visited.assign(n, false);
  order.clear();

  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs1(i);
    }
  }

  reverse(order.begin(), order.end());
  int label = 0;
  for (int v : order) {
    if (component[v] == -1) {
      dfs2(v, label);
      label++;
    }
  }

  vector<unordered_set<int>> graph_cond(label);
  for (auto &e : original_edges) {
    int a = e.first, b = e.second;
    int x = component[a], y = component[b];
    if (x != y) {
      graph_cond[x].insert(y);
    }
  }

  vector<pair<int, int>> edges_cond;
  for (int x = 0; x < label; x++) {
    for (int y : graph_cond[x]) {
      edges_cond.emplace_back(x, y);
    }
  }

  vector<pair<int, int>> edges_reduction;

  for (auto &e : edges_cond) {
    int x = e.first, y = e.second;

    queue<int> q;
    vector<bool> visited_bfs(label, false);
    q.push(x);
    visited_bfs[x] = true;
    bool found = false;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : graph_cond[u]) {
        if (u == x && v == y)
          continue;
        if (v == y) {
          found = true;
          break;
        }
        if (!visited_bfs[v]) {
          visited_bfs[v] = true;
          q.push(v);
        }
      }
      if (found)
        break;
    }

    if (!found) {
      edges_reduction.push_back(e);
    }
  }

  map<pair<int, int>, vector<pair<int, int>>> component_to_edges;
  for (auto &e : original_edges) {
    int a = e.first, b = e.second;
    int x = component[a], y = component[b];
    if (x != y) {
      component_to_edges[{x, y}].emplace_back(a, b);
    }
  }

  vector<pair<int, int>> selected_edges;

  for (auto &e : edges_reduction) {
    int x = e.first, y = e.second;
    auto &possible_edges = component_to_edges[{x, y}];
    if (!possible_edges.empty()) {
      selected_edges.push_back(possible_edges[0]);
    }
  }

  vector<vector<int>> components(label);
  for (int i = 0; i < n; i++) {
    components[component[i]].push_back(i);
  }

  vector<pair<int, int>> cycle_edges;

  for (int c = 0; c < label; c++) {
    auto &comp = components[c];
    int k = comp.size();
    if (k <= 1)
      continue;

    sort(comp.begin(), comp.end());

    for (int i = 0; i < k; i++) {
      int a = comp[i];
      int b = comp[(i + 1) % k];
      cycle_edges.emplace_back(a, b);
    }
  }

  vector<pair<int, int>> new_edges;
  for (auto &e : selected_edges) {
    new_edges.emplace_back(e.first + 1, e.second + 1);
  }
  for (auto &e : cycle_edges) {
    new_edges.emplace_back(e.first + 1, e.second + 1);
  }

  cout << new_edges.size() << '\n';
  for (auto &e : new_edges) {
    cout << e.first << ' ' << e.second << '\n';
  }

  return 0;
}
