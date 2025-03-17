#include <bits/stdc++.h>
using namespace std;

void kuhn(const vector<vector<int>> &graph, vector<int> &p, int v) {
  vector<bool> used(graph.size(), false);
  function<bool(int)> ku = [&](int u) {
    if (used[u]) {
      return false;
    }
    used[u] = true;
    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i];
      if (p[v] == -1 || ku(p[v])) {
        p[v] = u;
        return true;
      }
    }
    return false;
  };

  ku(v);
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<bool> used(n);
  vector<int> p(m, -1);
  vector<vector<int>> graph(n, vector<int>());

  for (int i = 0; i < n; ++i) {
    int cur;
    cin >> cur;
    while (cur != 0) {
      graph[i].push_back(cur - 1);
      cin >> cur;
    }
  }

  for (int i = 0; i < n; ++i) {
    kuhn(graph, p, i);
  }

  int count = 0;
  for (int i = 0; i < m; ++i) {
    if (p[i] != -1) {
      ++count;
    }
  }

  cout << count << '\n';

  for (int i = 0; i < m; ++i) {
    if (p[i] != -1) {
      cout << p[i] + 1 << ' ' << i + 1 << '\n';
    }
  }

  return 0;
}
