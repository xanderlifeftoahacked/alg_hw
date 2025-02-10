#include <bits/stdc++.h>
using namespace std;

vector<int> find_cutpoints(vector<vector<int>> &graph) {
  vector<bool> visited(graph.size(), false);
  vector<int> up(graph.size(), 1e9);
  vector<int> tin(graph.size(), 1e9);
  vector<int> ans;
  int time = 0;
  int child_count = 0;

  function<void(int, int)> dfs = [&](int v, int p) {
    visited[v] = true;
    tin[v] = up[v] = ++time;

    for (auto u : graph[v]) {
      if (u == p)
        continue;

      if (!visited[u]) {
        if (p == -1) {
          ++child_count;
        }
        dfs(u, v);
        up[v] = min(up[v], up[u]);

        if (up[u] >= tin[v] && p != -1) {
          ans.push_back(v);
        }
      } else {
        up[v] = min(tin[u], up[v]);
      }
    }
  };

  dfs(0, -1);

  if (child_count > 1)
    ans.push_back(0);

  return ans;
}

int main() {
  int n, m;

  cin >> n >> m;
  vector<vector<int>> graph(n + m, vector<int>());

  unordered_map<int, int> pillows;

  int a, b, c;

  for (size_t i = n; i < m + n; ++i) {
    cin >> a >> b >> c;
    --a, --b, --c;
    graph[i].push_back(a);
    graph[i].push_back(b);
    graph[i].push_back(c);
    graph[a].push_back(i);
    graph[b].push_back(i);
    graph[c].push_back(i);
  }

  auto ans = find_cutpoints(graph);

  set<int> ans_new;
  for (auto a : ans) {
    if (a < n)
      continue;
    ans_new.insert(a - n + 1);
  }

  cout << ans_new.size() << '\n';
  for (auto elem : ans_new) {
    cout << elem << ' ';
  }
  cout << '\n';

  return 0;
}
