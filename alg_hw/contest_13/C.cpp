#include <bits/stdc++.h>
using namespace std;

bool dfs(int u, const vector<vector<int>>& graph, vector<bool>& used, vector<int>& p) {
  if (used[u])
    return false;
  used[u] = true;
  for (int v : graph[u]) {
    if (p[v] == -1 || dfs(p[v], graph, used, p)) {
      p[v] = u;
      return true;
    }
  }
  return false;
}

vector<int> max_matching(const vector<vector<int>>& graph, int m, int n) {
  vector<int> p(n, -1);
  for (int u = 0; u < m; ++u) {
    vector<bool> used(m, false);
    dfs(u, graph, used, p);
  }
  return p;
}

void solve() {
  int m, n;
  cin >> m >> n;

  vector<vector<int>> original_graph(m);
  for (int i = 0; i < m; ++i) {
    int cur;
    cin >> cur;
    while (cur != 0) {
      original_graph[i].push_back(cur - 1);
      cin >> cur;
    }
  }

  vector<vector<int>> complement_graph(m);
  for (int i = 0; i < m; ++i) {
    unordered_set<int> known_girls(original_graph[i].begin(), original_graph[i].end());
    for (int j = 0; j < n; ++j) {
      if (known_girls.find(j) == known_girls.end()) {
        complement_graph[i].push_back(j);
      }
    }
  }

  vector<int> p = max_matching(complement_graph, m, n);

  vector<bool> visited_boys(m, false);
  vector<bool> visited_girls(n, false);
  queue<int> q;

  for (int u = 0; u < m; ++u) {
    bool matched = false;
    for (int v : complement_graph[u]) {
      if (p[v] == u) {
        matched = true;
        break;
      }
    }
    if (!matched) {
      visited_boys[u] = true;
      q.push(u);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : complement_graph[u]) {
      if (p[v] != u) {
        if (!visited_girls[v]) {
          visited_girls[v] = true;
          if (p[v] != -1 && !visited_boys[p[v]]) {
            visited_boys[p[v]] = true;
            q.push(p[v]);
          }
        }
      }
    }
  }

  vector<int> invited_boys, invited_girls;
  for (int u = 0; u < m; ++u) {
    if (visited_boys[u]) {
      invited_boys.push_back(u + 1);
    }
  }
  for (int v = 0; v < n; ++v) {
    if (!visited_girls[v]) {
      invited_girls.push_back(v + 1);
    }
  }

  int total = invited_boys.size() + invited_girls.size();
  cout << total << '\n';
  cout << invited_boys.size() << ' ' << invited_girls.size() << '\n';

  sort(invited_boys.begin(), invited_boys.end());
  for (int b : invited_boys) {
    cout << b << ' ';
  }
  cout << '\n';

  sort(invited_girls.begin(), invited_girls.end());
  for (int g : invited_girls) {
    cout << g << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
