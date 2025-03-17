#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll

// https://informatics.msk.ru/mod/statements/view.php?id=10845&chapterid=111981#1

struct Vertex {
  int to, cost;
};

void find_path(const vector<vector<Vertex>> &graph, int from, int end) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  vector<int> dist(graph.size(), LLONG_MAX);
  vector<int> p(graph.size(), -1);
  dist[from] = 0;
  pq.push({0, from});

  int first;
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d > dist[v])
      continue;

    for (auto [to, cost] : graph[v]) {
      if (dist[v] + cost >= dist[to])
        continue;

      dist[to] = dist[v] + cost;
      pq.push({dist[to], to});
      p[to] = v;
    }
  }

  if (dist[end] == LLONG_MAX) {
    cout << "-1\n";
    return;
  }

  int current = end;
  vector<int> path;
  while (current != -1) {
    path.push_back(current);
    current = p[current];
  }

  reverse(path.begin(), path.end());

  cout << path[1] << ' ' << path[path.size() - 2] << ' ' << dist[end] << '\n';
};

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<Vertex>> graph(n + 2);

  int temp;
  for (int i = 1; i <= n; ++i) {
    cin >> temp;
    if (temp == 1) {
      graph[0].push_back({i, 0});
    }
    if (temp == 2) {
      graph[i].push_back({n + 1, 0});
    }
  }

  int from, to, cost;
  while (m--) {
    cin >> from >> to >> cost;
    graph[from].push_back({to, cost});
    graph[to].push_back({from, cost});
  }

  find_path(graph, 0, n + 1);
}

signed main() {
  cin.tie(0);
  cout.tie(0);
  srand(time(0));

  ios_base::sync_with_stdio(0);

  size_t t = 1;
  while (t--)
    solve();

  return 0;
}
