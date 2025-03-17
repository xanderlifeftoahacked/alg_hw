#include <bits/stdc++.h>
using namespace std;

#define INF 1e18
#define ll long long

int main() {
  int N, S, F;
  cin >> N >> S >> F;
  S--;
  F--;
  vector<vector<int>> graph(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> graph[i][j];
    }
  }
  vector<ll> dist(N, INF);
  vector<bool> visited(N, false);
  dist[S] = 0;
  for (int i = 0; i < N; ++i) {
    int u = -1;
    for (int j = 0; j < N; ++j) {
      if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
        u = j;
      }
    }
    if (u == -1 || dist[u] == INF) {
      break;
    }
    visited[u] = true;
    for (int v = 0; v < N; ++v) {
      if (graph[u][v] != -1) {
        if (dist[v] > dist[u] + graph[u][v]) {
          dist[v] = dist[u] + graph[u][v];
        }
      }
    }
  }
  if (dist[F] == INF) {
    cout << -1 << '\n';
  } else {
    cout << dist[F] << '\n';
  }
  return 0;
}
