#include <iostream>

template <class T> class Queue {
  struct Node {
    T value;
    Node *next;
    Node(T val) : value{val}, next{nullptr} {}
  };

  Node *head;
  Node *tail;
  size_t sz;

public:
  Queue() : head{nullptr}, tail{nullptr}, sz{0} {}

  ~Queue() { clear(); }

  T front() {
    if (head)
      return head->value;
    throw std::runtime_error("Queue is empty");
  }

  size_t size() { return sz; }

  void clear() {
    while (head) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    sz = 0;
  }

  void push(T val) {
    Node *node = new Node(val);
    if (tail != nullptr) {
      tail->next = node;
    } else {
      head = node;
    }
    tail = node;
    ++sz;
  }

  T pop() {
    if (head) {
      Node *temp = head;
      T val = head->value;
      head = head->next;
      delete temp;
      --sz;
      if (sz == 0) {
        tail = nullptr;
      }
      return val;
    } else {
      throw std::runtime_error("Queue is empty");
    }
  }
};
int main() {
  Queue<int> queue;

  std::string command;

  while (std::getline(std::cin, command)) {
    try {
      if (command.substr(0, 4) == "push") {
        int n = std::stoi(command.substr(5));
        queue.push(n);
        std::cout << "ok\n";
      } else if (command == "pop") {
        std::cout << queue.pop() << '\n';
      } else if (command == "front") {
        std::cout << queue.front() << '\n';
      } else if (command == "size") {
        std::cout << queue.size() << '\n';
      } else if (command == "clear") {
        queue.clear();
        std::cout << "ok\n";
      } else if (command == "exit") {
        std::cout << "bye\n";
        break;
      }
    } catch (...) {
      std::cout << "error\n";
    }
  }
  return 0;
}
