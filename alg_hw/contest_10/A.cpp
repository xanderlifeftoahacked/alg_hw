#include <bits/stdc++.h>

using namespace std;

struct DSU {
  vector<int> parents;
  vector<int> ranks;
  vector<list<int>> parts;
  DSU(int n) {
    parents.resize(n);
    ranks.resize(n);
    for (size_t i = 0; i < n; ++i) {
      parents[i] = i;
      ranks[i] = 0;
      parts.push_back({(int)i});
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
    if (ranks[a] > ranks[b])
      swap(a, b);

    parents[a] = b;

    if (ranks[a] == ranks[b])
      ++ranks[b];
    parts[b].splice(parts[b].end(), parts[a]);
  }
};

int main() {
  int n;
  cin >> n;

  DSU dsu(n);

  int a, b;
  for (size_t i = 0; i < n - 1; ++i) {
    cin >> a >> b;
    --a, --b;
    dsu.unite(a, b);
  }

  auto ans = dsu.parts[dsu.find(0)];

  for (auto cat : ans) {
    cout << cat + 1 << ' ';
  }
  cout << '\n';
}
