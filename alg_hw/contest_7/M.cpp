#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>

std::string rotate_cw(std::string arr) {
  std::string new_arr = std::string(arr.begin() + 1, arr.end()) + arr[0];
  return new_arr;
}

std::string rotate_ccw(std::string arr) {
  std::string new_arr = arr.back() + std::string(arr.begin(), arr.end() - 1);
  return new_arr;
}

int main() {
  int a, b;
  std::cin >> a >> b;

  std::queue<int> queue;
  std::vector<int> parents(10000, -100);
  std::vector<bool> visited(10000, false);

  visited[a] = true;
  parents[a] = -1;
  queue.push(a);

  while (!queue.empty()) {
    int cur = queue.front();
    queue.pop();
    std::vector<int> turns = {std::stoi(rotate_ccw(std::to_string(cur))), std::stoi(rotate_cw(std::to_string(cur)))};
    if (cur < 9000) {
      turns.push_back(cur + 1000);
    }
    if (cur % 10 > 1) {
      turns.push_back(cur - 1);
    }
    for (auto neigh : turns) {
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

  std::reverse(ans.begin(), ans.end());
  for (auto v : ans) {
    std::cout << v << '\n';
  }

  return 0;
}
