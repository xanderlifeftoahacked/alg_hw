#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int N;
  cin >> N;
  vector<vector<ll>> d(N, vector<ll>(N));

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> d[i][j];
    }
  }

  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  ll max_dist = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      max_dist = max(max_dist, d[i][j]);
    }
  }

  cout << max_dist << '\n';
  return 0;
}
