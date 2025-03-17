#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=16816&chapterid=170#1

struct Vertex {
  int to, t1, t2;
};

int find_dist(const vector<vector<Vertex>> &graph, int from, int to) {
  vector<int> d(graph.size(), INT_MAX);
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  d[from] = 0;
  pq.push({0, from});

  while (!pq.empty()) {
    int v = pq.top().first;
    pq.pop();

    for (auto [to, t1, t2] : graph[v]) {
      if (d[v] > t1)
        continue;

      int w = t2;
      if (w < d[to]) {
        d[to] = w;
        pq.push({d[to], to});
      }
    }
  }

  return d[to];
};

void solve() {
  int n, d, v, r;
  cin >> n >> d >> v >> r;

  vector<vector<Vertex>> graph(n);

  int from, to, t1, t2;
  while (r--) {
    cin >> from >> t1 >> to >> t2;
    --from, --to;
    graph[from].push_back({to, t1, t2});
  }

  int dist = find_dist(graph, --d, --v);
  if (dist == INT_MAX) {
    cout << "-1\n";
  } else
    cout << dist << '\n';
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
