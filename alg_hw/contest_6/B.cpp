#include <iostream>
#include <vector>

template <class T> class Stack {
  std::vector<T> stack;

public:
  void push(T n) { stack.push_back(n); }

  T pop() {
    T top = stack.back();
    stack.pop_back();
    return top;
  }

  size_t back() { return stack.back(); }

  size_t size() { return stack.size(); }

  void clear() { stack.clear(); }
};

int main() {
  Stack<int> stack;
  std::string command;

  while (std::getline(std::cin, command)) {
    if (command.substr(0, 4) == "push") {
      int n = std::stoi(command.substr(5));
      stack.push(n);
      std::cout << "ok\n";
    } else if (command == "pop") {
      if (stack.size() == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << stack.pop() << '\n';
    } else if (command == "back") {
      if (stack.size() == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << stack.back() << '\n';
    } else if (command == "size") {
      std::cout << stack.size() << '\n';
    } else if (command == "clear") {
      stack.clear();
      std::cout << "ok\n";
    } else if (command == "exit") {
      std::cout << "bye\n";
      break;
    }
  }

  return 0;
}
