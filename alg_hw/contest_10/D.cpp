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
      weights[i] = 0;
    }
  }

  int find(int a) {
    if (parents[a] != a)
      parents[a] = find(parents[a]);
    return parents[a];
  }

  void unite(int a, int b, int w) {
    a = find(a);
    b = find(b);
    if (a == b) {
      weights[b] += w;
      return;
    }
    if (weights[a] > weights[b])
      swap(a, b);

    parents[a] = b;

    weights[b] += weights[a] + w;
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);

  int q, x, y, w;
  while (m--) {
    cin >> q;
    if (q == 1) {
      cin >> x >> y >> w;
      --x, --y;
      dsu.unite(x, y, w);
    } else {
      cin >> x;
      --x;
      cout << dsu.weights[dsu.find(x)] << '\n';
    }
  }
}
