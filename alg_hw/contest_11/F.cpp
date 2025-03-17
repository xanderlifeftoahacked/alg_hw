#include <bits/stdc++.h>
using namespace std;

#define INF 1e18
#define ll long long

int main() {
  int N;
  cin >> N;
  vector<vector<ll>> d(N, vector<ll>(N));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> d[i][j];

  for (int k = 0; k < N; ++k)
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

  bool has_negative_cycle = false;
  for (int i = 0; i < N; ++i)
    if (d[i][i] < 0) {
      has_negative_cycle = true;
      break;
    }

  if (has_negative_cycle) {
    cout << -1 << '\n';
    return 0;
  }

  ll min_dist = INF;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i != j)
        min_dist = min(min_dist, d[i][j]);

  cout << min_dist << '\n';
  return 0;
}
