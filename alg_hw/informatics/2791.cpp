#include <bits/stdc++.h>
using namespace std;
#define ll long long

// https://informatics.msk.ru/mod/statements/view.php?id=1974&chapterid=2791#1

struct Node {
  ll x;
  ll val;
  ll y;
  Node *left;
  Node *right;

  Node(ll _x) : x{_x}, val{1}, y{rand()}, left{nullptr}, right{nullptr} {}
};

struct Pivo {
  Node *root = nullptr;

  ll sum(Node *v) { return (v ? v->val : 0LL); }

  void upd(Node *v) {
    if (!v)
      return;
    v->val = 1 + sum(v->left) + sum(v->right);
  }

  Node *merge(Node *a, Node *b) {
    if (a == nullptr)
      return b;
    if (b == nullptr)
      return a;

    if (a->y > b->y) {
      a->right = merge(a->right, b);
      upd(a);
      return a;
    }
    b->left = merge(a, b->left);
    upd(b);
    return b;
  }

  pair<Node *, Node *> split(Node *a, ll k) {
    if (!a) {
      return {nullptr, nullptr};
    }

    if (sum(a->left) >= k) {
      auto [l, r] = split(a->left, k);
      a->left = r;
      upd(a);
      return {l, a};
    }

    auto [l, r] = split(a->right, k - sum(a->left) - 1);
    a->right = l;
    upd(a);
    return {a, r};
  }

  void add(ll x) {
    auto [l, r] = split(root, x);
    Node *t = new Node(x);
    root = merge(l, merge(t, r));
  }

  void move_to_start(ll l, ll r) {
    auto [l1, l2] = split(root, l - 1);
    auto [r1, r2] = split(l2, r - l + 1);
    root = merge(r1, merge(l1, r2));
  }
};

void in_order(Node *start) {
  if (!start)
    return;
  in_order(start->left);
  cout << start->x << ' ';
  in_order(start->right);
}

void solve() {
  size_t n, m;
  cin >> n >> m;

  Pivo pivo;
  for (size_t i = 1; i <= n; ++i) {
    pivo.add(i);
  }

  int l, r;
  while (m--) {
    cin >> l >> r;
    pivo.move_to_start(l, r);
  }

  in_order(pivo.root);
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  srand(time(0));

  size_t t = 1;
  while (t--)
    solve();

  return 0;
}
