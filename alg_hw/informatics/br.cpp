#include <bits/stdc++.h>

using namespace std;

set<int> find_cutpoints(const vector<vector<int>> &graph, int s) {
  vector<bool> visited(graph.size(), false);
  vector<int> tin(graph.size());
  vector<int> up(graph.size());
  set<int> ans;
  int time = 0;

  function<void(int, int)> dfs = [&](int v, int p) {
    visited[v] = true;
    int child_cnt = 0;
    tin[v] = up[v] = ++time;

    for (auto u : graph[v]) {
      if (v == p) {
        continue;
      }
      if (!visited[u]) {
        ++child_cnt;
        dfs(u, v);
        up[v] = min(up[u], up[v]);

        if (up[u] >= tin[v] && p != -1) {
          ans.insert(v);
        }
      } else {
        up[v] = min(tin[u], up[v]);
      }
    }

    if (p == -1 && child_cnt > 1) {
      ans.insert(v);
    }
  };

  for (size_t v = 0; v < graph.size(); ++v) {
    if (!visited[v])
      dfs(v, -1);
  }

  return ans;
}

set<int> cp_on_path(const vector<vector<int>> &graph, int s, int e, const set<int> &cutpoints) {
  queue<int> q;
  vector<bool> visited(graph.size());
  set<int> ans;

  q.push(s);
  visited[s] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    visited[cur] = true;
    if (cur == e)
      break;
    if (cutpoints.count(cur))
      ans.insert(cur);

    for (auto to : graph[cur]) {
      if (visited[to])
        continue;

      q.push(to);
    }
  }

  return ans;
}

int main() {
  size_t n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n);
  int a, b;
  while (m--) {
    cin >> a >> b;
    --a, --b;

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int s, e;
  cin >> s >> e;
  --s, --e;

  auto cutpoints = find_cutpoints(graph, s);
  auto ans = cp_on_path(graph, s, e, cutpoints);

  cout << ans.size() << '\n';
  for (auto e : ans) {
    cout << ++e << ' ';
  }
  cout << endl;

  return 0;
}
