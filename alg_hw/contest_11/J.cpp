#include <bits/stdc++.h>

using namespace std;

#define INF 1e18
#define EPS 1e-9

int main() {
  int N, M, S, E;
  cin >> N >> M;
  cin >> S >> E;
  --S, --E;

  vector<vector<double>> graph(N, vector<double>(N, INF));

  int s, e, p;
  for (int i = 0; i < M; ++i) {
    cin >> s >> e >> p;
    --s, --e;

    double prob = 1.0 - p / 100.0;
    if (prob < EPS) {
      continue;
    }

    double weight = -log(prob);
    if (weight < graph[s][e]) {
      graph[s][e] = weight;
      graph[e][s] = weight;
    }
  }

  vector<double> dist(N, INF);
  vector<bool> visited(N, false);
  dist[S] = 0.0;

  for (int i = 0; i < N; ++i) {
    int u = -1;
    for (int j = 0; j < N; ++j) {
      if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
        u = j;
      }
    }

    if (u == -1 || dist[u] >= INF) {
      break;
    }

    visited[u] = true;

    for (int v = 0; v < N; ++v) {
      if (graph[u][v] < INF && !visited[v]) {
        if (dist[v] > dist[u] + graph[u][v]) {
          dist[v] = dist[u] + graph[u][v];
        }
      }
    }
  }

  double ans = exp(-dist[E]);

  cout << fixed << setprecision(15) << 1.0 - ans << endl;

  return 0;
}
