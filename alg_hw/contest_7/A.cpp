#include <iostream>
#include <vector>
#include <cstdint>

#define ll int64_t

int main() {
  ll N, M;
  std::cin >> N >> M;
  std::vector<int> perecs(N);

  for (size_t i = 0; i < M; ++i) {
    ll a, b;
    std::cin >> a >> b;

    ++perecs[a - 1];
    ++perecs[b - 1];
  }

  for (auto elem : perecs) {
    std::cout << elem << ' ';
  }

  return 0;
}
