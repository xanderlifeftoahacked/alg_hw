#include <bits/stdc++.h>
using namespace std;

#define INF 1e18
#define ll long long

struct State {
  int x;
  ll cost;
  int steps;
  State(int x, ll cost, int steps) : x(x), cost(cost), steps(steps) {}
  bool operator<(const State &other) const {
    if (cost != other.cost)
      return cost > other.cost;
    return steps > other.steps;
  }
};

struct Parent {
  int prev_x;
  int y;
  char op;
  Parent() : prev_x(-1), y(0), op(' ') {}
  Parent(int px, int y, char op) : prev_x(px), y(y), op(op) {}
};

int sum_digits(int y) {
  int sum = 0;
  while (y > 0) {
    sum += y % 10;
    y /= 10;
  }
  return sum;
}

vector<int> get_ys(int x) {
  string s = to_string(x);
  set<int> ys;
  for (int i = 0; i < s.size(); ++i) {
    for (int j = i; j < s.size(); ++j) {
      string sub = s.substr(i, j - i + 1);
      int y = stoi(sub);
      if (y > 0) {
        ys.insert(y);
      }
    }
  }
  return vector<int>(ys.begin(), ys.end());
}

int main() {
  int n, a, b;
  cin >> n >> a >> b;

  if (a == b) {
    cout << "0\n0\n";
    return 0;
  }

  vector<pair<ll, int>> dist(n + 1, {INF, 0});
  vector<Parent> parent(n + 1);

  priority_queue<State> pq;
  dist[a].first = 0;
  pq.emplace(a, 0, 0);

  bool found = false;

  while (!pq.empty()) {
    State s = pq.top();
    pq.pop();
    int x = s.x;
    ll cost = s.cost;
    int steps = s.steps;

    if (x == b) {
      found = true;
      vector<string> path;
      int current = b;
      while (current != a) {
        Parent p = parent[current];
        string op = string(1, p.op) + to_string(p.y);
        path.push_back(op);
        current = p.prev_x;
      }
      reverse(path.begin(), path.end());
      cout << cost << '\n';
      cout << path.size() << '\n';
      for (const string &op : path) {
        cout << op << '\n';
      }
      return 0;
    }

    if (cost > dist[x].first ||
        (cost == dist[x].first && steps > dist[x].second))
      continue;

    vector<int> ys = get_ys(x);
    for (int y : ys) {
      int new_x_add = x + y;
      if (new_x_add <= n) {
        ll new_cost = cost + sum_digits(y);
        int new_steps = steps + 1;
        if (new_cost < dist[new_x_add].first ||
            (new_cost == dist[new_x_add].first &&
             new_steps < dist[new_x_add].second)) {
          dist[new_x_add].first = new_cost;
          dist[new_x_add].second = new_steps;
          parent[new_x_add] = Parent(x, y, '+');
          pq.emplace(new_x_add, new_cost, new_steps);
        }
      }
      int new_x_sub = x - y;
      if (new_x_sub >= 1) {
        ll new_cost = cost + sum_digits(y);
        int new_steps = steps + 1;
        if (new_cost < dist[new_x_sub].first ||
            (new_cost == dist[new_x_sub].first &&
             new_steps < dist[new_x_sub].second)) {
          dist[new_x_sub].first = new_cost;
          dist[new_x_sub].second = new_steps;
          parent[new_x_sub] = Parent(x, y, '-');
          pq.emplace(new_x_sub, new_cost, new_steps);
        }
      }
    }
  }

  cout << "-1\n";
  return 0;
}
