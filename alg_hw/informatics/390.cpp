#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=12590&chapterid=390#1

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
      if (u == p) {
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

set<int> bfs01(const vector<vector<int>> &graph, const set<int> &cutpoints,
               int s, int e) {
  size_t n = graph.size();
  vector<int> d(n, INT_MAX);
  vector<int> prev(n, -1);

  deque<int> dq;
  d[s] = 0;
  dq.push_front(s);

  while (!dq.empty()) {
    int v = dq.front();
    dq.pop_front();

    for (auto u : graph[v]) {
      int w = cutpoints.count(u) ? 1 : 0;

      if (d[v] + w < d[u]) {
        d[u] = d[v] + w;
        prev[u] = v;

        if (w == 0)
          dq.push_front(u);
        else
          dq.push_back(u);
      }
    }
  }
  set<int> path;
  for (int v = e; v != -1; v = prev[v]) {
    if (cutpoints.count(v) && v != s && v != e)
      path.insert(v);
  }

  return path;
}

void solve() {
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
  auto ans = bfs01(graph, cutpoints, s, e);

  cout << ans.size() << '\n';
  for (auto elem : ans) {
    cout << ++elem << '\n';
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  srand(time(0));

  ios_base::sync_with_stdio(0);

  size_t t = 1;
  while (t--)
    solve();

  return 0;
}
