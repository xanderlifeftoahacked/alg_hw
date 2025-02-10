#include <bits/stdc++.h>
using namespace std;

map<string, int> items_vk;
vector<int> indeg;
vector<string> items;

function<bool(int, int)> comp;

vector<int> topsort(vector<set<int, decltype(comp)>>& graph) {
  int n = graph.size();
  vector<bool> visited(n, false);
  vector<int> order;

  function<void(int)> dfs = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (!visited[u]) {
        dfs(u);
      }
    }
    order.push_back(v);
  };

  vector<int> sources;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      sources.push_back(i);
    }
  }

  sort(sources.begin(), sources.end(), [&](int a, int b) { return items[a] < items[b]; });

  for (int v : sources) {
    if (!visited[v]) {
      dfs(v);
    }
  }

  reverse(order.begin(), order.end());
  return order;
}

int main() {
  int n, m;
  cin >> n >> m;
  comp = [&](int lhs, int rhs) { return items[lhs] < items[rhs]; };
  items.resize(n);
  indeg.resize(n, 0);

  for (int i = 0; i < n; ++i) {
    int id;
    string name;
    cin >> id >> ws;
    getline(cin, name);
    items[id - 1] = name;
    items_vk[name] = id - 1;
  }

  vector<set<int, decltype(comp)>> graph(n, set<int, decltype(comp)>(comp));

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    graph[a].insert(b);
    ++indeg[b];
  }

  vector<int> order = topsort(graph);

  for (int elem : order) {
    cout << items[elem] << '\n';
  }

  return 0;
}
