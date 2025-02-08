#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

void tarjan(int v, std::vector<std::vector<int>>& graph, std::vector<int>& ids, std::vector<int>& low,
            std::vector<bool>& onStack, std::stack<int>& st, int& id, std::vector<int>& sccSizes) {
  ids[v] = low[v] = id++;
  st.push(v);
  onStack[v] = true;

  for (int to : graph[v]) {
    if (ids[to] == -1) {
      tarjan(to, graph, ids, low, onStack, st, id, sccSizes);
      low[v] = std::min(low[v], low[to]);
    } else if (onStack[to]) {
      low[v] = std::min(low[v], ids[to]);
    }
  }

  if (ids[v] == low[v]) {
    int size = 0;
    while (true) {
      int node = st.top();
      st.pop();
      onStack[node] = false;
      size++;
      if (node == v)
        break;
    }

    if (size > 1) {
      sccSizes.push_back(size);
    }
  }
}

int main() {
  int N;
  std::cin >> N;
  std::vector<std::vector<int>> graph(N);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    int keyLocation;
    std::cin >> keyLocation;
    graph[i].push_back(keyLocation - 1);
    if (keyLocation - 1 == i) {
      ++ans;
    }
  }

  std::vector<int> ids(N, -1);
  std::vector<int> low(N);
  std::vector<bool> onStack(N, false);
  std::stack<int> st;
  int id = 0;
  std::vector<int> sccSizes;

  for (int i = 0; i < N; i++) {
    if (ids[i] == -1) {
      tarjan(i, graph, ids, low, onStack, st, id, sccSizes);
    }
  }

  std::cout << sccSizes.size() + ans << '\n';
  return 0;
}
