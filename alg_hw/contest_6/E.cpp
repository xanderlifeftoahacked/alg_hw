#include <iostream>

template <class T>
class Deque {
  struct Node {
    T value;
    Node *next;
    Node *prev;
    Node(T val) : value{val}, next{nullptr}, prev{nullptr} {
    }
  };

  Node *head;
  Node *tail;
  size_t sz;

 public:
  Deque() : head{nullptr}, tail{nullptr}, sz{0} {
  }

  ~Deque() {
    clear();
  }

  void clear() {
    while (head) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    sz = 0;
  }

  void push_front(T val) {
    Node *node = new Node(val);
    if (head == nullptr) {
      head = tail = node;
    } else {
      node->next = head;
      head->prev = node;
      head = node;
    }
    ++sz;
  }

  void push_back(T val) {
    Node *node = new Node(val);
    if (tail == nullptr) {
      head = tail = node;
    } else {
      node->prev = tail;
      tail->next = node;
      tail = node;
    }
    ++sz;
  }

  T pop_front() {
    if (head) {
      Node *temp = head;
      T val = head->value;
      head = head->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      delete temp;
      --sz;
      return val;
    } else {
      throw std::runtime_error("Deque is empty");
    }
  }

  T pop_back() {
    if (tail) {
      Node *temp = tail;
      T val = tail->value;
      tail = tail->prev;
      if (tail) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
      delete temp;
      --sz;
      return val;
    } else {
      throw std::runtime_error("Deque is empty");
    }
  }

  T front() {
    if (head) {
      return head->value;
    } else {
      throw std::runtime_error("Deque is empty");
    }
  }

  T back() {
    if (tail) {
      return tail->value;
    } else {
      throw std::runtime_error("Deque is empty");
    }
  }
  size_t size() {
    return sz;
  }
};

int main() {
  Deque<int> dequeue;
  std::string command;

  while (std::getline(std::cin, command)) {
    try {
      if (command.substr(0, 9) == "push_back") {
        int n = std::stoi(command.substr(9));
        dequeue.push_back(n);
        std::cout << "ok\n";
      } else if (command.substr(0, 10) == "push_front") {
        int n = std::stoi(command.substr(10));
        dequeue.push_front(n);
        std::cout << "ok\n";
      } else if (command == "pop_front") {
        std::cout << dequeue.pop_front() << '\n';
      } else if (command == "pop_back") {
        std::cout << dequeue.pop_back() << '\n';
      } else if (command == "front") {
        std::cout << dequeue.front() << '\n';
      } else if (command == "back") {
        std::cout << dequeue.back() << '\n';
      } else if (command == "size") {
        std::cout << dequeue.size() << '\n';
      } else if (command == "clear") {
        dequeue.clear();
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
