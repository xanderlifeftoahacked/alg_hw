#include <bits/stdc++.h>
#include <climits>
using namespace std;
#define int long long

struct Info {
  int c;
  int f;
  Info() : c(0), f(0) {
  }
};

signed main() {
  int n;
  cin >> n;
  vector<pair<char, char>> cards(n + 1);
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    cards[i] = {s[0], s[1]};
  }
  string target;
  cin >> target;
  int m = target.size();
  if (m > n) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  vector<int> freq(26, 0);
  for (char c : target)
    freq[c - 'a']++;

  int V = 26 + n + 2;
  int source = 0, sink = V - 1;

  vector<vector<int>> graph(V);
  map<pair<int, int>, Info> edges;

  auto add_edge = [&](int u, int v, int cap) {
    graph[u].push_back(v);
    graph[v].push_back(u);
    edges[{u, v}].c += cap;
    if (!edges.count({v, u}))
      edges[{v, u}] = Info();
  };

  for (int i = 0; i < 26; ++i) {
    if (freq[i] > 0)
      add_edge(source, 1 + i, freq[i]);
  }

  for (int i = 1; i <= n; ++i) {
    int cardNode = 26 + i;
    char a = cards[i].first, b = cards[i].second;
    if (a == b) {
      int letterNode = 1 + (a - 'a');
      add_edge(letterNode, cardNode, 1);
    } else {
      int nodeA = 1 + (a - 'a');
      int nodeB = 1 + (b - 'a');
      add_edge(nodeA, cardNode, 1);
      add_edge(nodeB, cardNode, 1);
    }
    add_edge(cardNode, sink, 1);
  }

  int flow = 0;
  while (true) {
    vector<bool> visited(V, false);
    function<int(int, int)> dfs = [&](int v, int p) -> int {
      if (v == sink)
        return p;
      if (visited[v])
        return 0;
      visited[v] = true;
      for (int u : graph[v]) {
        if (edges[{v, u}].c > edges[{v, u}].f) {
          int delta = dfs(u, min(p, edges[{v, u}].c - edges[{v, u}].f));
          if (delta > 0) {
            edges[{v, u}].f += delta;
            edges[{u, v}].f -= delta;
            return delta;
          }
        }
      }
      return 0;
    };
    int pushed = dfs(source, INT_MAX);
    if (pushed == 0)
      break;
    flow += pushed;
  }

  if (flow != m) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  vector<char> cardAssigned(n + 1, 0);
  for (int i = 1; i <= 26; ++i) {
    for (int v : graph[i]) {
      if (v >= 27 && v <= 26 + n) {
        if (edges[{i, v}].f > 0) {
          int cardIndex = v - 26;
          cardAssigned[cardIndex] = 'a' + (i - 1);
        }
      }
    }
  }

  vector<vector<int>> letterToCards(26);
  for (int i = 1; i <= n; ++i) {
    if (cardAssigned[i] != 0)
      letterToCards[cardAssigned[i] - 'a'].push_back(i);
  }

  vector<int> ans(m, 0);
  vector<int> ptr(26, 0);
  for (int i = 0; i < m; ++i) {
    int letter = target[i] - 'a';
    int cardIndex = letterToCards[letter][ptr[letter]++];
    if (cards[cardIndex].first == target[i])
      ans[i] = cardIndex;
    else
      ans[i] = -cardIndex;
  }

  for (int i = 0; i < m; ++i)
    cout << ans[i] << " ";
  cout << "\n";
  return 0;
}
