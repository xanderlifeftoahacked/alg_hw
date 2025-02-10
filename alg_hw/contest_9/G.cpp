#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> find_bridges(vector<vector<ll>> &graph) {
  vector<bool> visited(graph.size(), false);
  vector<ll> up(graph.size(), 1e9);
  vector<ll> tin(graph.size(), 1e9);
  map<ll, ll> parents;
  map<ll, ll> weight_of_vert;
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
      int cur = -1;
      parents[v] = p;
      while (cur != v) {
        cur = buf.top();
        buf.pop();
        c2s[cur] = color;
      }
      ++weight_of_vert[v];
      ++color;
    }
  };

  dfs(0, -1);

  return c2s;
}

int main() {
  ll n, m;
  cin >> n >> m;

  vector<vector<ll>> graph(n, vector<ll>());

  ll a, b;
  while (m--) {
    cin >> a >> b;

    graph[--a].push_back(--b);
    graph[b].push_back(a);
  }

  auto c2s = find_bridges(graph);

  for (auto elem : c2s) {
    cout << elem << ' ';
  }

  map<int, int> elems_in_leafs;

  for (size_t v = 0; v < c2s.size(); ++v) {
    if (graph[v].size() == 1) {
      elems_in_leafs[]
    }
  }
}
