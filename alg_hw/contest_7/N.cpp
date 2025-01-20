#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

std::pair<int, int> bfs(std::unordered_map<int, std::vector<int>> &graph, int v) {
  std::queue<int> queue;
  std::vector<int> visited(graph.size());
  std::vector<int> dist(graph.size(), 0);
  int max_dist = -1;
  int max_v = -1;
  queue.push(v);
  visited[v] = true;

  while (!queue.empty()) {
    int cur = queue.front();
    queue.pop();
    for (auto neigh : graph[cur]) {
      if (visited[neigh])
        continue;
      visited[neigh] = true;

      dist[neigh] = dist[cur] + 1;
      if (dist[neigh] > max_dist) {
        max_dist = std::max(dist[neigh], max_dist);
        max_v = neigh;
      }
      queue.push(neigh);
    }
  }

  return {max_v, max_dist};
}

int main() {
  int n;
  std::cin >> n;

  std::unordered_map<int, std::vector<int>> graph;

  --n;
  while (n--) {
    int a, b;
    std::cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  std::cout << bfs(graph, bfs(graph, 0).first).second + 1 << '\n';

  return 0;
}
