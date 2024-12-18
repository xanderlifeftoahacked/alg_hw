#include <iostream>
#include <queue>

int main() {
  std::queue<int> first, second;
  for (size_t i = 0; i < 5; ++i) {
    int card;
    std::cin >> card;
    first.push(card);
  }
  for (size_t i = 0; i < 5; ++i) {
    int card;
    std::cin >> card;
    second.push(card);
  }

  size_t rounds = 0;
  while (!first.empty() && !second.empty() && rounds < 1e6) {
    int card1 = first.front();
    int card2 = second.front();
    first.pop();
    second.pop();

    if ((card1 > card2 && !(card1 == 9 && card2 == 0)) ||
        (card1 == 0 && card2 == 9)) {
      first.push(card1);
      first.push(card2);
    } else {
      second.push(card1);
      second.push(card2);
    }
    ++rounds;
  }

  if (first.empty()) {
    std::cout << "second " << rounds << '\n';
  } else if (second.empty()) {
    std::cout << "first " << rounds << '\n';
  } else {
    std::cout << "botva\n";
  }

  return 0;
}
