#include <bits/stdc++.h>
using namespace std;

void dodfs(vector<vector<int>> &graph) {
  vector<int> visited(graph.size());
}

int main() {
  size_t n, m;
  cin >> n >> m;

  auto graph = vector<vector<int>>(n, vector<int>());

  int a, b;
  for (size_t i = 0; i < m; ++i) {
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
  }

  return 0;
}
