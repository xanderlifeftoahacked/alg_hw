#include <bits/stdc++.h>
using namespace std;

void kuhn(const vector<vector<int>>& graph, vector<int>& p, int v) {
  vector<bool> used(graph.size(), false);
  function<bool(int)> ku = [&](int u) {
    if (used[u])
      return false;
    used[u] = true;
    for (int j : graph[u]) {
      if (p[j] == -1 || ku(p[j])) {
        p[j] = u;
        return true;
      }
    }
    return false;
  };
  ku(v);
}

int main() {
  int n;
  string name;
  cin >> n >> name;
  int m = name.size();
  vector<vector<int>> graph(m);

  string cube;
  for (int j = 0; j < n; ++j) {
    cin >> cube;
    for (char c : cube) {
      for (int i = 0; i < m; ++i) {
        if (name[i] == c) {
          if (find(graph[i].begin(), graph[i].end(), j) == graph[i].end()) {
            graph[i].push_back(j);
          }
        }
      }
    }
  }

  if (m > n) {
    cout << "NO\n";
    return 0;
  }

  vector<int> p(n, -1);
  for (int i = 0; i < m; ++i) {
    kuhn(graph, p, i);
  }

  int count = 0;
  for (int j = 0; j < n; ++j) {
    if (p[j] != -1) {
      ++count;
    }
  }

  if (count < m) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";
  vector<int> ans(m);
  for (int j = 0; j < n; ++j) {
    if (p[j] != -1) {
      ans[p[j]] = j + 1;
    }
  }
  for (int x : ans) {
    cout << x << ' ';
  }
  cout << '\n';

  return 0;
}
