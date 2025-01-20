#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::unordered_map<int, std::vector<int>> graph;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      int temp;
      std::cin >> temp;
      if (temp != 0) {
        graph[i].push_back(j);
      }
    }
  }
  int a, b;
  std::cin >> a >> b;
  --a;
  --b;

  std::queue<int> queue;
  std::vector<int> parents(n, -100);
  std::vector<bool> visited(n, false);

  visited[a] = true;
  parents[a] = -1;
  queue.push(a);

  while (!queue.empty()) {
    int cur = queue.front();
    queue.pop();
    for (auto neigh : graph[cur]) {
      if (visited[neigh])
        continue;

      visited[neigh] = true;
      queue.push(neigh);
      parents[neigh] = cur;
    }
  }

  std::vector<int> ans;
  int counter = 0;
  while (b >= 0) {
    ans.push_back(b);
    b = parents[b];
  }

  if (b == -100) {
    std::cout << "-1\n";
    return 0;
  }

  std::cout << ans.size() - 1 << '\n';

  if (ans.size() == 1) {
    return 0;
  }

  std::reverse(ans.begin(), ans.end());
  for (auto v : ans) {
    std::cout << v + 1 << ' ';
  }
  std::cout << '\n';

  return 0;
}
