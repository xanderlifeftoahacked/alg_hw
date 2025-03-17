#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=61665&chapterid=904#1
// гроб

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

void solve() {
  int n, m;
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
  int p5, q5, p6, q6;
  cin >> p5 >> q5 >> p6 >> q6;

  vector<Edge> mst;
  for (size_t i = 0; i < edges.size(); ++i) {
    Edge edge = edges[i];
    if (dsu.united(edge.from, edge.to))
      continue;

    dsu.unite(edge.from, edge.to);
    mst.push_back(edge);
  }

  if (mst.size() != n - 1) {
    cout << "Impossible\n";
    return;
  }

  ll total_length = 0;
  for (auto &e : mst) {
    total_length += e.cost;
  }

  if (total_length > q6 + q5) {
    cout << "Impossible\n";
    return;
  }

  bool use6 = false;
  if (p5 > p6)
    swap(p5, p6), swap(q5, q6), use6 = true;

  int required_min_sum = max(0, (int)(total_length - q6));

  vector<bool> dp(q5 + 1, false);
  dp[0] = true;
  vector<vector<int>> prev(mst.size() + 1, vector<int>(q5 + 1, -1));

  for (int i = 0; i < mst.size(); ++i) {
    int len = mst[i].cost;
    for (int j = q5; j >= len; --j) {
      if (dp[j - len] && !dp[j]) {
        dp[j] = true;
        prev[i + 1][j] = j - len;
      }
    }
  }
  int best_sum = -1;
  for (int s = q5; s >= required_min_sum; --s) {
    if (dp[s]) {
      best_sum = s;
      break;
    }
  }

  if (best_sum == -1 || total_length - best_sum > q6) {
    cout << "Impossible\n";
    return;
  }

  ll total_cost = best_sum * p5 + (total_length - best_sum) * p6;

  vector<bool> selected(mst.size(), false);
  int current_sum = best_sum;
  for (int i = mst.size(); i > 0; --i) {
    if (prev[i][current_sum] != -1) {
      selected[i - 1] = true;
      current_sum = prev[i][current_sum];
    }
  }

  cout << total_cost << '\n';

  vector<pair<int, int>> result;
  for (int i = 0; i < mst.size(); ++i) {
    int cat;
    if (selected[i]) {
      cat = use6 ? 6 : 5;
    } else {
      cat = use6 ? 5 : 6;
    }
    result.emplace_back(mst[i].id, cat);
  }

  sort(result.begin(), result.end());

  for (auto &p : result) {
    cout << p.first << ' ' << p.second << '\n';
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);

  size_t t = 1;
  while (t--)
    solve();

  return 0;
}
