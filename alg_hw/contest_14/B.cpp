#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
  ll key;
  size_t left_idx;
  size_t right_idx;
};

bool is_bst(const vector<Node>& nodes, size_t current_idx, ll min_val, ll max_val) {
  const Node& current = nodes[current_idx];
  if (current.key <= min_val || current.key > max_val) {
    return false;
  }

  bool left_ok = true;
  if (current.left_idx != (size_t)-1) {
    left_ok = is_bst(nodes, current.left_idx, min_val, current.key);
  }

  bool right_ok = true;
  if (current.right_idx != (size_t)-1) {
    right_ok = is_bst(nodes, current.right_idx, current.key, max_val);
  }

  return left_ok && right_ok;
}

void solve() {
  size_t n;
  cin >> n;

  vector<Node> nodes(n);
  ll val;
  size_t left, right;
  for (size_t idx = 0; idx < n; ++idx) {
    cin >> val >> left >> right;
    nodes[idx] = {val, left, right};
  }

  if (is_bst(nodes, 0, LLONG_MIN, LLONG_MAX)) {
    cout << "CORRECT\n";
  } else {
    cout << "INCORRECT\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  size_t t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
