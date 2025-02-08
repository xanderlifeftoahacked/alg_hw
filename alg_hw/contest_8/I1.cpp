#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

#define ll long long

using tp = std::tuple<ll, ll, ll, ll>;

ll calc_time(ll start, ll start_time, ll speed, ll pos) {
  return start_time + (pos - start) * speed;
}

std::vector<ll> top_sort(std::vector<std::vector<ll>> &graph) {
  std::vector<bool> visited(graph.size(), false);
  std::vector<ll> ans;

  std::function<void(ll)> dfs = [&](ll v) {
    visited[v] = true;
    for (auto u : graph[v]) {
      if (!visited[u])
        dfs(u);
    }
    ans.push_back(v);
  };

  for (ll i = 0; i < graph.size(); ++i) {
    if (visited[i])
      continue;
    dfs(i);
  }

  std::reverse(std::begin(ans), std::end(ans));

  return ans;
}

int main() {
  ll n;
  std::cin >> n;

  auto graph = std::vector<std::vector<ll>>(n);
  auto trains = std::vector<tp>(n);

  for (size_t i = 0; i < n; ++i) {
    ll station_start, station_end, time_start, speed;
    std::cin >> station_start >> station_end >> time_start >> speed;
    trains[i] = {station_start, station_end, time_start, speed};
  }

  for (size_t prev = 0; prev < n; ++prev) {
    auto [s_start_prev, s_end_prev, t_start_prev, speed_prev] = trains[prev];
    for (size_t i = prev + 1; i < n; ++i) {
      auto [s_start, s_end, t_start, speed] = trains[i];

      ll overlap_start = std::max(s_start, s_start_prev);

      if (overlap_start > std::min(s_end, s_end_prev))
        continue;

      ll t2 = calc_time(s_start, t_start, speed, overlap_start);
      ll t1 = calc_time(s_start_prev, t_start_prev, speed_prev, overlap_start);

      if (t1 < t2) {
        graph[prev].push_back(i);
      } else {
        graph[i].push_back(prev);
      }
    }
  }

  auto res = top_sort(graph);

  for (auto elem : res) {
    std::cout << elem + 1 << ' ';
  }
  std::cout << '\n';

  return 0;
}
