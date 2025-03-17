#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
  int N, M;
  cin >> N;
  vector<int> cost(N);

  for (int i = 0; i < N; ++i) {
    cin >> cost[i];
  }

  cin >> M;
  vector<vector<pair<int, int>>> graph(N);

  int u, v;
  while (M--) {
    cin >> u >> v;
    u--;
    v--;
    graph[u].emplace_back(v, cost[u]);
    graph[v].emplace_back(u, cost[v]);
  }

  vector<int> dist(N, INF);
  dist[0] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.emplace(0, 0);

  while (!pq.empty()) {
    int current_dist = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (current_dist > dist[u])
      continue;

    for (auto &edge : graph[u]) {
      int v = edge.first;
      int w = edge.second;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pq.emplace(dist[v], v);
      }
    }
  }

  if (dist[N - 1] == INF) {
    cout << -1 << endl;
  } else {
    cout << dist[N - 1] << endl;
  }

  return 0;
}
