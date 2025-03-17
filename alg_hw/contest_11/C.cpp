#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Edge {
  int from;
  int to;
  ll t_from;
  ll t_to;
  Edge(int f, int t, ll tf, ll tt) : from(f), to(t), t_from(tf), t_to(tt) {}
};

int main() {
  int N, E, M;
  cin >> N >> E >> M;
  --E;

  vector<Edge> edges;

  for (int m = 0; m < M; ++m) {
    int K;
    cin >> K;
    vector<pair<int, ll>> stops;
    for (int k = 0; k < K; ++k) {
      int station;
      ll time;
      cin >> station >> time;
      station--;
      stops.push_back({station, time});
    }
    for (int i = 0; i < K; ++i) {
      for (int j = i + 1; j < K; ++j) {
        if (stops[i].second <= stops[j].second) {
          edges.emplace_back(stops[i].first, stops[j].first, stops[i].second,
                             stops[j].second);
        }
      }
    }
  }

  vector<ll> dist(N, LLONG_MAX);
  dist[0] = 0;

  for (int i = 0; i < N - 1; ++i) {
    for (const Edge &e : edges) {
      if (dist[e.from] != LLONG_MAX && dist[e.from] <= e.t_from &&
          dist[e.to] > e.t_to) {
        dist[e.to] = e.t_to;
      }
    }
  }

  if (dist[E] == LLONG_MAX) {
    cout << -1 << endl;
  } else {
    cout << dist[E] << endl;
  }

  return 0;
}
