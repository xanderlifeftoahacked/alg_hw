#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int main() {
  std::string input;
  std::getline(std::cin, input);

  std::stringstream ss(input);
  std::stack<int> s;
  std::string token;

  while (ss >> token) {
    if (isdigit(token[0])) {
      s.push(std::stoi(token));
    } else {
      int b = s.top();
      s.pop();
      int a = s.top();
      s.pop();
      if (token == "+") {
        s.push(a + b);
      } else if (token == "-") {
        s.push(a - b);
      } else if (token == "*") {
        s.push(a * b);
      }
    }
  }

  std::cout << s.top() << '\n';

  return 0;
}
