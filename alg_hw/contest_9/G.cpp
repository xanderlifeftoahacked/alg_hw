#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define MOD 1'000'000'007

vector<ll> find_bridges(vector<vector<ll>> &graph) {
  vector<bool> visited(graph.size(), false);
  vector<ll> up(graph.size(), 1e9);
  vector<ll> tin(graph.size(), 1e9);
  stack<ll> buf;
  vector<ll> c2s(graph.size(), 0);

  ll color = 1;
  ll timer = 0;

  function<void(ll, ll)> dfs = [&](ll v, ll p) {
    buf.push(v);
    visited[v] = true;
    tin[v] = up[v] = ++timer;

    for (auto to : graph[v]) {
      if (to == p)
        continue;

      if (!visited[to]) {
        dfs(to, v);
        up[v] = min(up[v], up[to]);
      } else {
        up[v] = min(up[v], tin[to]);
      }
    }

    if (up[v] == tin[v] && p != -1) {
      ll cur = -1;
      while (cur != v) {
        cur = buf.top();
        buf.pop();
        c2s[cur] = color;
      }
      ++color;
    }
  };

  dfs(0, -1);

  if (!buf.empty()) {
    ll cur = -1;
    while (!buf.empty()) {
      cur = buf.top();
      buf.pop();
      c2s[cur] = color;
    }
    ++color;
  }

  return c2s;
}

int main() {
  ll n, m;
  cin >> n >> m;

  vector<vector<ll>> graph(n);

  ll a, b;
  while (m--) {
    cin >> a >> b;
    --a;
    --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  auto c2s = find_bridges(graph);

  map<ll, ll> counts;
  for (auto color : c2s) {
    counts[color]++;
  }

  set<pair<ll, ll>> component_edges;

  for (ll u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      if (c2s[u] != c2s[v]) {
        ll c1 = c2s[u];
        ll c2 = c2s[v];
        if (c1 > c2)
          swap(c1, c2);
        component_edges.insert({c1, c2});
      }
    }
  }

  map<ll, vector<ll>> component_graph;
  for (auto &edge : component_edges) {
    ll c1 = edge.first, c2 = edge.second;
    component_graph[c1].push_back(c2);
    component_graph[c2].push_back(c1);
  }

  vector<ll> leaf_colors;
  for (auto &[k, v] : component_graph) {
    if (v.size() == 1) {
      leaf_colors.push_back(k);
    }
  }

  vector<ll> leaf_weights;
  for (auto color : leaf_colors) {
    leaf_weights.push_back(counts[color]);
  }

  if (leaf_weights.size() == 0) {
    cout << "1 " << n << '\n';
    return 0;
  }

  cout << leaf_weights.size() << ' ';
  uint64_t ans = 1;
  for (auto w : leaf_weights) {
    ans = (ans * w) % MOD;
  }
  cout << ans << '\n';

  return 0;
}
