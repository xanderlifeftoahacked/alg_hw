#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> dijkstra(int start, int end,
                     const vector<vector<pair<int, int>>> &graph,
                     vector<int> &parent) {
  int N = graph.size();
  vector<int> dist(N, INF);
  dist[start] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, start});
  parent.assign(N, -1);

  while (!pq.empty()) {
    int u = pq.top().second;
    int current_dist = pq.top().first;
    pq.pop();

    if (current_dist > dist[u])
      continue;
    if (u == end)
      break;

    for (const auto &edge : graph[u]) {
      int v = edge.first;
      int w = edge.second;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        parent[v] = u;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

vector<int> get_path(int start, int end, const vector<int> &parent) {
  vector<int> path;
  for (int v = end; v != -1; v = parent[v]) {
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  if (path.empty() || path[0] != start)
    return {};
  return path;
}

int main() {
  int N, K, M;
  cin >> N >> K >> M;
  --K;

  int end = N - 1;

  vector<vector<pair<int, int>>> graph(N);
  int u, v, len;
  for (int i = 0; i < M; ++i) {
    cin >> u >> v >> len;
    --u, --v;
    graph[u].emplace_back(v, len);
    graph[v].emplace_back(u, len);
  }

  vector<int> parent_forward;
  vector<int> dist_forward = dijkstra(K, end, graph, parent_forward);
  if (dist_forward[end] == INF) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> path_forward = get_path(K, end, parent_forward);
  if (path_forward.empty()) {
    cout << -1 << '\n';
    return 0;
  }

  set<pair<int, int>> edges_to_remove;
  for (int i = 0; i < path_forward.size() - 1; ++i) {
    int u = path_forward[i], v = path_forward[i + 1];
    edges_to_remove.insert({u, v});
    edges_to_remove.insert({v, u});
  }

  vector<vector<pair<int, int>>> new_graph(N);
  for (int u = 0; u < N; ++u) {
    for (const auto &edge : graph[u]) {
      int v = edge.first, len = edge.second;
      if (!edges_to_remove.count({u, v})) {
        new_graph[u].emplace_back(v, len);
      }
    }
  }

  vector<int> parent_backward;
  vector<int> dist_backward = dijkstra(end, K, new_graph, parent_backward);
  if (dist_backward[K] == INF) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> path_backward = get_path(end, K, parent_backward);
  if (path_backward.empty()) {
    cout << -1 << '\n';
    return 0;
  }

  cout << dist_forward[end] << ' ' << dist_backward[K] << '\n';
  for (int v : path_forward)
    cout << v + 1 << ' ';
  cout << '\n';
  for (int v : path_backward)
    cout << v + 1 << ' ';
  cout << '\n';

  return 0;
}
