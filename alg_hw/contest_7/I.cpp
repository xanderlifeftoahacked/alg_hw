#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::unordered_map<std::string, std::vector<std::string>> graph;
  std::unordered_map<std::string, bool> visited;
  std::map<std::string, int> dist;
  std::unordered_map<std::string, int> indeg;

  --n;
  while (n--) {
    std::string child, parent;
    std::cin >> child >> parent;
    graph[parent].push_back(child);
    visited[parent] = false;
    visited[child] = false;
    ++indeg[child];
    if (indeg.count(parent) == 0) {
      indeg[parent] = 0;
    }

    dist[parent] = 0;
    dist[child] = 0;
  }

  std::string parent;
  for (auto elem : indeg) {
    if (elem.second == 0) {
      parent = elem.first;
      break;
    }
  }

  std::queue<std::string> queue;
  queue.push(parent);

  while (!queue.empty()) {
    std::string cur = queue.front();
    queue.pop();

    for (auto neigh : graph[cur]) {
      if (visited[neigh])
        continue;

      visited[neigh] = true;
      queue.push(neigh);
      dist[neigh] = dist[cur] + 1;
    }
  }

  for (auto elem : dist) {
    std::cout << elem.first << ' ' << elem.second << '\n';
  }

  return 0;
}
