#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
  int N, M, K, S, F;
  cin >> N >> M >> K >> S >> F;
  --S, --F;

  vector<vector<pair<int, int>>> graph(N);
  int u, v, p;
  for (int i = 0; i < M; ++i) {
    cin >> u >> v >> p;
    --u, --v;
    graph[u].emplace_back(v, p);
  }

  vector<vector<ll>> dp(K + 1, vector<ll>(N, INF));
  dp[0][S] = 0;

  for (int step = 1; step <= K; ++step) {
    vector<ll> current(N, INF);
    for (int u = 0; u < N; ++u) {
      if (dp[step - 1][u] == INF)
        continue;
      for (auto &edge : graph[u]) {
        int v = edge.first;
        int p = edge.second;
        if (current[v] > dp[step - 1][u] + p) {
          current[v] = dp[step - 1][u] + p;
        }
      }
    }
    dp[step] = std::move(current);
  }

  ll result = INF;
  for (int step = 1; step <= K; ++step) {
    result = min(result, dp[step][F]);
  }

  if (result == INF) {
    cout << -1 << '\n';
  } else {
    cout << result << '\n';
  }

  return 0;
}
