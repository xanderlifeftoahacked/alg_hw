#include <iostream>
#include <vector>
#include <cstdint>

const int64_t p1 = 31;
const int64_t mod1 = 1e9 + 9;

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result % modulus;
}

int64_t get_hash(const std::vector<int64_t>& prefix_hash, int64_t l, int64_t r, int64_t pp, int64_t mmod) {
  int64_t hash = (prefix_hash[r + 1] - (prefix_hash[l] * modpow(pp, r - l + 1, mmod) % mmod) + mmod) % mmod;

  if (hash < 0) {
    hash += mmod;
  }

  return hash;
}

int main() {
  int64_t n = 0, k = 0;
  std::cin >> n >> k;

  std::vector<int64_t> str(n);

  std::vector<int64_t> prefix_hash(n + 1);
  std::vector<int64_t> suffix_hash(n + 1);

  std::vector<int64_t> ans;

  for (size_t i = 0; i < n; ++i) {
    std::cin >> str[i];
  }

  std::vector<int64_t> str_rev = std::vector<int64_t>(std::rbegin(str), std::rend(str));

  prefix_hash[0] = 0;
  suffix_hash[0] = 0;

  for (size_t i = 1; i < n; ++i) {
    prefix_hash[i] = (((prefix_hash[i - 1] * p1) % mod1) + str[i - 1]) % mod1;
    suffix_hash[i] = (((suffix_hash[i - 1] * p1) % mod1) + str[i - 1]) % mod1;
  }

  for (int64_t i = 1; i <= n; ++i) {
    int64_t center = n - i;

    if (center == 0) {
      ans.push_back(i);
      continue;
    }

    int64_t start = 2 * i - n;
    if (start < 0) {
      continue;
    }

    int64_t hash_f = get_hash(prefix_hash, 0, center, p1, mod1);
    int64_t hash_b = get_hash(suffix_hash, start, i, p1, mod1);
    if (hash_f == hash_b) {
      ans.push_back(i);
    }
  }

  for (auto elem : ans) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  return 0;
}
