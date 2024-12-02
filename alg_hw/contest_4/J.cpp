#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <cmath>

struct Point {
  double x;
  double y;
};

double find_path_length(const std::vector<Point> &points, size_t point_idx) {
  double ans = 0;
  for (size_t i = 0; i < point_idx; ++i) {
    ans += std::sqrt(std::pow(points[i].x - points[i + 1].x, 2) + std::pow(points[i].y - points[i + 1].y, 2));
  }
  return ans;
}

int main() {
  size_t n = 0, l = 0;
  std::cin >> n >> l;

  Point a, b;

  std::cin >> a.x >> a.y >> b.x >> b.y;

  if (a.x > b.x) {
    std::swap(a, b);
  }

  std::vector<Point> points(n + 2);

  points[n] = a;
  points[n + 1] = b;

  for (size_t i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  std::sort(std::begin(points), std::end(points), [](auto lhs, auto rhs) { return lhs.x < rhs.x; });

  std::stack<Point> stack;

  for (size_t i = 0; i < n; ++i) {
    while (stack.top().y <= points[i].y) {
      Point temp = stack.top();
      stack.pop();
      double bridge_length = points[i].x - stack.top().x;
      if (bridge_length > l) {
        double H = (stack.top().x - temp.y) * l / bridge_length;
        double x2 = ((temp.y + H) - temp.y) / (stack.top().y - temp.y) * (stack.top().x - temp.x) + temp.x;
        double y = temp.y + H;
      }
    }
    stack.push(points[i]);
  }

  return 0;
}
