#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=61665&chapterid=1316#1

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
pair<ll, vector<Edge>> mst_price(const vector<Edge> &edges,
                                 const int excluded_edge) {
  DSU dsu(n);
  ll ans = 0;

  vector<Edge> mst;
  for (size_t i = 0; i < edges.size(); ++i) {
    Edge edge = edges[i];
    if (edge.id == excluded_edge)
      continue;
    if (dsu.united(edge.from, edge.to))
      continue;

    dsu.unite(edge.from, edge.to);
    ans += edge.cost;
    mst.push_back(edge);
  }

  return {ans, mst};
}

void solve() {
  cin >> n >> m;

  vector<Edge> edges;
  DSU dsu(n);

  for (size_t id = 1; id <= m; ++id) {
    Edge temp;
    cin >> temp.from >> temp.to >> temp.cost;
    temp.id = id;
    --temp.from, --temp.to;
    edges.push_back(temp);
  }

  sort(edges.begin(), edges.end());

  auto [ans1, first_mst] = mst_price(edges, -1);
  ll ans2 = LLONG_MAX;
  for (auto &edge : first_mst) {
    auto [new_ans, m] = mst_price(edges, edge.id);
    if (m.size() == n - 1)
      ans2 = min(ans2, new_ans);
  }

  cout << ans1 << ' ' << ans2 << '\n';
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
