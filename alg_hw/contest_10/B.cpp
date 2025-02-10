#include <bits/stdc++.h>

using namespace std;

struct DSU {
  vector<int> parents;
  vector<int> ranks;
  DSU(int n) {
    parents.resize(n);
    ranks.resize(n);
    for (size_t i = 0; i < n; ++i) {
      parents[i] = i;
      ranks[i] = 0;
    }
  }

  int find(int a) {
    if (parents[a] != a)
      parents[a] = find(parents[a]);
    return parents[a];
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;
    if (ranks[a] > ranks[b])
      swap(a, b);

    parents[a] = b;

    if (ranks[a] == ranks[b])
      ++ranks[b];
  }
};

enum class TYPE { ask, cut };
struct Question {
  TYPE type;
  int a;
  int b;
};

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  DSU dsu(n);

  int a, b;
  while (m--) {
    cin >> a >> b;
  }

  stack<Question> questions;
  string query;
  while (k--) {
    cin >> query >> a >> b;
    --a;
    --b;
    if (query == "ask") {
      questions.push({TYPE::ask, a, b});
    } else {
      questions.push({TYPE::cut, a, b});
    }
  }

  Question cur;

  stack<string> answers;
  while (!questions.empty()) {
    cur = questions.top();
    questions.pop();
    if (cur.type == TYPE::ask) {
      if (dsu.find(cur.a) == dsu.find(cur.b)) {
        answers.push("YES");
      } else {
        answers.push("NO");
      }
    } else {
      dsu.unite(cur.a, cur.b);
    }
  }

  while (!answers.empty()) {
    cout << answers.top() << '\n';
    answers.pop();
  }

  return 0;
}
