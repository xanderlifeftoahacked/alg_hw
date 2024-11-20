#include <iostream>
#include <set>

template <typename Comp>
bool check_partition(const std::multiset<int, Comp> &segments, const int target,
                     const size_t k) {
  int ans = 0;
  for (int segment : segments) {
    if (segment < target) {
      break;
    }
    while (segment >= target) {
      segment -= target;
      ++ans;
    }
  }

  return ans >= k;
}

int main() {
  size_t n = 0, k = 0;
  std::cin >> n >> k;

  auto comp = [](int lhs, int rhs) { return lhs >= rhs; };
  std::multiset<int, decltype(comp)> segments(comp);

  int temp = 0;
  while (n--) {
    std::cin >> temp;
    segments.insert(temp);
  }

  int l = 0, r = *(segments.begin()) + 1;

  while (l < r - 1) {
    int m = l + (r - l) / 2;

    if (check_partition(segments, m, k)) {
      l = m;
    } else {
      r = m;
    }
  }

  std::cout << l << '\n';

  return 0;
}
