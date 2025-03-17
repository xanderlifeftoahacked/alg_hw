#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
  int key;
  size_t left_idx;
  size_t right_idx;
};

void in_order(Node start, const vector<Node> &nodes) {
  if (start.left_idx != -1)
    in_order(nodes[start.left_idx], nodes);
  cout << start.key << ' ';
  if (start.right_idx != -1)
    in_order(nodes[start.right_idx], nodes);
}

void pre_order(Node start, const vector<Node> &nodes) {
  cout << start.key << ' ';
  if (start.left_idx != -1)
    pre_order(nodes[start.left_idx], nodes);
  if (start.right_idx != -1)
    pre_order(nodes[start.right_idx], nodes);
}

void post_order(Node start, const vector<Node> &nodes) {
  if (start.left_idx != -1)
    post_order(nodes[start.left_idx], nodes);
  if (start.right_idx != -1)
    post_order(nodes[start.right_idx], nodes);
  cout << start.key << ' ';
}

void solve() {
  size_t n;
  cin >> n;

  vector<Node> nodes(n);
  int val;
  size_t left, right;
  for (size_t idx = 0; idx < n; ++idx) {
    cin >> val >> left >> right;
    nodes[idx] = {val, left, right};
  }

  in_order(nodes[0], nodes);
  cout << '\n';
  pre_order(nodes[0], nodes);
  cout << '\n';
  post_order(nodes[0], nodes);
  cout << '\n';
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
