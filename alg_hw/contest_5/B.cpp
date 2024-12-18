#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

const int64_t p1 = 7;
const int64_t mod1 = 1e9 + 7;

const int64_t p2 = 11;
const int64_t mod2 = 1e9 + 9;

struct StringHash {
  std::pair<int64_t, int64_t> hashes;
  int64_t size;
  int64_t left;

  friend bool operator<(const StringHash& left, const StringHash& right) {
    if (left.hashes < right.hashes) {
      return true;
    }
    if (right.hashes < left.hashes) {
      return false;
    }

    if (left.left < right.left) {
      return true;
    }

    return false;
  }
};

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
  if (l == 0) {
    return prefix_hash[r];
  }
  return (prefix_hash[r] - (prefix_hash[l - 1] * modpow(pp, r - l + 1, mmod) % mmod) + mmod) % mmod;
}

int main() {
  std::string s;
  std::cin >> s;
  std::vector<char> str(s.size());
  for (size_t i = 0; i < s.size(); ++i) {
    str[i] = s[i];
  }

  std::vector<int64_t> prefix_hashes1(s.size());
  std::vector<int64_t> prefix_hashes2(s.size());

  prefix_hashes1[0] = str[0];
  prefix_hashes2[0] = str[0];
  for (size_t i = 1; i < s.size(); ++i) {
    prefix_hashes1[i] = (((prefix_hashes1[i - 1] * p1) % mod1) + str[i]) % mod1;
    prefix_hashes2[i] = (((prefix_hashes2[i - 1] * p2) % mod2) + str[i]) % mod2;
  }

  auto comp = [](StringHash l, StringHash r) { return l < r; };

  std::vector<StringHash> hashes_vec;
  for (int64_t l = 0; l < s.size(); ++l) {
    for (int64_t r = l; r < s.size(); ++r) {

      int64_t hash1 = get_hash(prefix_hashes1, l, r, p1, mod1);
      int64_t hash2 = get_hash(prefix_hashes2, l, r, p2, mod2);

      hashes_vec.push_back({{hash1, hash2}, r - l + 1, l});
    }
  }

  std::sort(hashes_vec.begin(), hashes_vec.end(), comp);
  size_t ans = 0;
  for (size_t i = 0; i < hashes_vec.size(); ++i) {
    size_t r = i;

    if (r + 1 > hashes_vec.size() - 1) {
      continue;
    }
    while (hashes_vec[i].hashes == hashes_vec[r + 1].hashes) {
      ++r;
    }

    if (hashes_vec[i].hashes == hashes_vec[r].hashes && hashes_vec[i].left + hashes_vec[i].size <= hashes_vec[r].left) {
      ++ans;
    }

    i = r;
  }

  std::cout << ans << '\n';

  return 0;
}
