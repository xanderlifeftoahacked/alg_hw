#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?chapterid=1928#1

void solve() {
  int n;
  cin >> n;

  vector<int> prices(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> prices[i];
  }

  vector<vector<int>> graph(n);
  int k, u;
  for (size_t v = 0; v < n; ++v) {
    cin >> k;
    while (k--) {
      cin >> u;
      graph[v].push_back(--u);
    }
  }

  vector<bool> visited(n, false);
  ll ans = prices[0];
  vector<int> order;

  function<void(int)> dfs = [&](int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (visited[u])
        continue;
      ans += prices[u];
      dfs(u);
    }
    order.push_back(v);
  };

  dfs(0);
  cout << ans << ' ' << order.size() << '\n';

  for (auto elem : order) {
    cout << ++elem << ' ';
  }

  cout << '\n';
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
