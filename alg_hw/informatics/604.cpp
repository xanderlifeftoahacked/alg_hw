#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=567&chapterid=604#1

struct DSU {
  vector<ll> parents;
  vector<ll> ranks;
  DSU(ll n) {
    parents.resize(n);
    ranks.resize(n, 0);
    iota(parents.begin(), parents.end(), 0);
  }

  ll find(ll a) {
    if (parents[a] != a) {
      parents[a] = find(parents[a]);
    }
    return parents[a];
  }

  bool united(ll a, ll b) { return find(a) == find(b); }

  void unite(ll a, ll b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;

    if (ranks[b] > ranks[a])
      swap(a, b);

    if (ranks[a] == ranks[b])
      ++ranks[a];

    parents[b] = a;
  }
};

struct Edge {
  int from, to, cost, id;

  bool operator<(const Edge &other) const { return this->cost < other.cost; }
};

int n, m;
pair<ll, vector<Edge>> mst_price(const vector<Edge> &edges, DSU &dsu) {
  ll ans = 0;

  vector<Edge> mst;
  for (size_t i = 0; i < edges.size(); ++i) {
    Edge edge = edges[i];

    if (dsu.united(edge.from, edge.to))
      continue;

    dsu.unite(edge.from, edge.to);
    ans += edge.cost;
    mst.push_back(edge);
  }

  return {ans, mst};
}

void solve() {
  cin >> n;

  vector<Edge> edges;

  DSU dsu(n);
  int price = 0, id = 0;
  Edge temp;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      cin >> price;

      if (!price)
        continue;

      temp.from = i;
      temp.to = j;
      temp.cost = price;
      edges.push_back(temp);
    }
  }
  bool a;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      cin >> a;
      if (a)
        dsu.unite(i, j);
    }
  }

  sort(edges.begin(), edges.end());

  auto [ans1, first_mst] = mst_price(edges, dsu);

  cout << ans1 << '\n';
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
