#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

struct Triplet {
  int64_t first;
  int64_t second;
  int64_t third;
};

int64_t count_d(const int64_t first, const int64_t second,
                const int64_t third) {
  return ((first - second) * (first - second) +
          (first - third) * (first - third) +
          (second - third) * (second - third));
}

std::vector<int64_t> find_candidates(const std::vector<int64_t> &in,
                                     const int64_t elem) {
  std::vector<int64_t> ans;

  auto r = std::upper_bound(std::begin(in), std::end(in), elem);

  if (r != std::end(in)) {
    ans.push_back(*r);
  }

  if (r != std::begin(in)) {
    ans.push_back(*(r - 1));
  }

  return ans;
}

int main() {
  size_t t = 0;
  std::cin >> t;

  size_t n_r = 0, n_g = 0, n_b = 0;
  while (t--) {
    std::cin >> n_r >> n_g >> n_b;

    std::vector<int64_t> r_gems(n_r);
    std::vector<int64_t> g_gems(n_g);
    std::vector<int64_t> b_gems(n_b);

    for (size_t i = 0; i < n_r; ++i) {
      std::cin >> r_gems[i];
    }
    for (size_t i = 0; i < n_g; ++i) {
      std::cin >> g_gems[i];
    }
    for (size_t i = 0; i < n_b; ++i) {
      std::cin >> b_gems[i];
    }

    std::sort(std::begin(r_gems), std::end(r_gems));
    std::sort(std::begin(g_gems), std::end(g_gems));
    std::sort(std::begin(b_gems), std::end(b_gems));

    int64_t min_delta = std::numeric_limits<int64_t>::max();
    Triplet min_triplet;
    for (auto const elem : r_gems) {
      auto cands_1 = find_candidates(g_gems, elem);
      auto cands_2 = find_candidates(b_gems, elem);

      for (auto const first : cands_1) {
        for (auto const second : cands_2) {
          int64_t delta = count_d(elem, first, second);

          if (delta < min_delta) {
            min_delta = delta;
            min_triplet = {elem, first, second};
          }
        }
      }
    }

    for (auto const elem : g_gems) {
      auto cands_1 = find_candidates(r_gems, elem);
      auto cands_2 = find_candidates(b_gems, elem);

      for (auto const first : cands_1) {
        for (auto const second : cands_2) {
          int64_t delta = count_d(first, elem, second);

          if (delta < min_delta) {
            min_delta = delta;
            min_triplet = {first, elem, second};
          }
        }
      }
    }

    for (auto const elem : b_gems) {
      auto cands_1 = find_candidates(r_gems, elem);
      auto cands_2 = find_candidates(g_gems, elem);

      for (auto const first : cands_1) {
        for (auto const second : cands_2) {
          int64_t delta = count_d(first, elem, second);

          if (delta < min_delta) {
            min_delta = delta;
            min_triplet = {first, second, elem};
          }
        }
      }
    }

    std::cout << min_triplet.first << ' ' << min_triplet.second << ' '
              << min_triplet.third << '\n';
  }

  return 0;
}
