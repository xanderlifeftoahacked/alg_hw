#include <bits/stdc++.h>

using namespace std;

struct DSU {
  vector<int> parents;
  vector<int> weights;
  DSU(int n) {
    parents.resize(n);
    weights.resize(n);
    for (size_t i = 0; i < n; ++i) {
      parents[i] = i;
      weights[i] = 1;
    }
  }

  int find(int a) {
    if (parents[a] != a)
      parents[a] = find(parents[a]);
    return parents[a];
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;
    if (weights[a] > weights[b])
      swap(a, b);

    parents[a] = b;

    weights[b] += weights[a];
  }
};

struct Edge {
  int u;
  int v;
  int w;

  bool operator<(const Edge& other) {
    return w < other.w;
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);
  vector<Edge> edges;

  int a, b, w;
  while (m--) {
    cin >> a >> b >> w;
    --a, --b;
    edges.push_back({a, b, w});
  }

  sort(edges.begin(), edges.end());
  long long ans = 0;
  int edges_cnt = 0;

  for (auto edge : edges) {
    if (dsu.find(edge.u) == dsu.find(edge.v))
      continue;

    dsu.unite(edge.u, edge.v);
    ans += edge.w;
    if (edges_cnt == n - 1)
      break;
  }
  cout << ans << '\n';

  return 0;
}
