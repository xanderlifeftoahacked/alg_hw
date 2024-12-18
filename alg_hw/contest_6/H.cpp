#include <iostream>
#include <stack>

bool is_valid(std::string s) {
  std::stack<char> stack;

  for (const auto ch : s) {
    if (ch == '(' || ch == '[' || ch == '{') {
      stack.push(ch);
      continue;
    }

    if (stack.size() == 0) {
      return false;
    }

    if (ch == ')' && stack.top() != '(') {
      return false;
    }

    if (ch == '}' && stack.top() != '{') {
      return false;
    }

    if (ch == ']' && stack.top() != '[') {
      return false;
    }
    stack.pop();
  }

  if (stack.size() != 0) {
    return false;
  }
  return true;
}

int main() {
  std::string s;
  std::cin >> s;

  if (is_valid(s)) {
    std::cout << "yes\n";
  } else {
    std::cout << "no\n";
  }

  return 0;
}
