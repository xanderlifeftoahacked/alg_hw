#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#define ll long long
#define MOD 1000000001

struct Node {
  ll x;
  ll sum;
  ll y;
  Node* left;
  Node* right;

  Node(ll _x) : x{_x}, sum{_x}, y{rand()}, left{nullptr}, right{nullptr} {
  }
};

struct Pivo {
  Node* root = nullptr;

  ll sum(Node* v) {
    return (v ? v->sum : 0LL);
  }

  void upd(Node* v) {
    if (!v)
      return;
    v->sum = sum(v->left) + sum(v->right) + v->x;
  }

  Node* merge(Node* a, Node* b) {
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

  pair<Node*, Node*> split(Node* a, ll k) {
    if (!a) {
      return {nullptr, nullptr};
    }

    if (a->x < k) {
      auto [l, r] = split(a->right, k);
      a->right = l;
      upd(a);
      return {a, r};
    }
    auto [l, r] = split(a->left, k);
    a->left = r;
    upd(a);
    return {l, a};
  }

  Node* remove(Node* a, ll x) {
    if (a == nullptr)
      return nullptr;
    if (a->x == x) {
      Node* res = merge(a->left, a->right);
      delete a;
      return res;
    } else if (x < a->x) {
      a->left = remove(a->left, x);
    } else {
      a->right = remove(a->right, x);
    }
    upd(a);
    return a;
  }

  bool find(Node* root, ll x) {
    if (!root)
      return false;
    if (root->x == x)
      return true;
    if (x < root->x) {
      return find(root->left, x);
    } else {
      return find(root->right, x);
    }
  }

  void add(ll x) {
    if (find(root, x)) {
      return;
    }

    auto [l, r] = split(root, x);
    Node* t = new Node(x);
    root = merge(l, merge(t, r));
  }

  ll sum(ll l, ll r) {
    auto [l1, l2] = split(root, l);
    auto [r1, r2] = split(l2, r + 1);
    ll res = sum(r1);
    root = merge(l1, merge(r1, r2));
    return res;
  }
};

ll last_s = 0;
ll f(ll x) {
  return (x + last_s) % MOD;
}

void solve() {
  size_t n;
  cin >> n;

  Pivo pivo;
  while (n--) {
    char q;
    ll val;
    cin >> q >> val;
    if (q == '+') {
      pivo.add(f(val));
    } else if (q == '-') {
      pivo.root = pivo.remove(pivo.root, f(val));
    } else if (q == '?') {
      if (pivo.find(pivo.root, f(val)))
        cout << "Found\n";
      else
        cout << "Not found\n";
    } else if (q == 's') {
      ll sec;
      cin >> sec;
      ll res = pivo.sum(f(val), f(sec));
      last_s = res;
      cout << res << '\n';
    }
  }
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
