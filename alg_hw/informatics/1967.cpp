#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll

// https://informatics.msk.ru/mod/statements/view.php?id=16816&chapterid=1967#1

struct Vertex {
  int to, cost, max_w;
};

bool is_good(const vector<vector<Vertex>> &graph, int from, int end,
             int weight) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  vector<int> dist(graph.size(), LLONG_MAX);
  dist[from] = 0;
  pq.push({0, from});

  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d > dist[v])
      continue;

    for (auto [to, cost, max_w] : graph[v]) {
      if (weight > max_w)
        continue;

      if (dist[v] + cost >= dist[to])
        continue;

      dist[to] = dist[v] + cost;
      pq.push({dist[to], to});
    }
  }

  return dist[end] <= 1440;
};

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<Vertex>> graph(n);
  if (n == 1) {
    cout << "10000000\n";
    return;
  }

  int from, to, cost, max_w;
  while (m--) {
    cin >> from >> to >> cost >> max_w;
    --from, --to;
    graph[from].push_back({to, cost, max((max_w - 3000000) / 100, 0LL)});
    graph[to].push_back({from, cost, max((max_w - 3000000) / 100, 0LL)});
  }

  int l = -1, r = 1e9, mid = 0;
  while (l < r - 1) {
    mid = l + (r - l) / 2;
    if (is_good(graph, 0, n - 1, mid))
      l = mid;
    else
      r = mid;
  }
  cout << (l >= 0 ? l : 0) << '\n';
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
