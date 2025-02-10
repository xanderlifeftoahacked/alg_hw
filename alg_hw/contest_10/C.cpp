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

int main() {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);

  int a, b;
  for (size_t i = 1; i <= m; ++i) {
    cin >> a >> b;
    dsu.unite(a, b);

    if (dsu.weights[dsu.find(0)] == n) {
      cout << i << '\n';
      break;
    }
  }
}
