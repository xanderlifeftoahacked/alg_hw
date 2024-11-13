#include <cstdint>
#include <iostream>
#include <string>

int64_t count_digits(int64_t num) {
  if (num == 0)
    return 0;
  int64_t count = 0;
  int64_t digits = 1;
  int64_t current = 9;

  while (num > 0) {
    if (num >= current) {
      count += current * digits;
      num -= current;
    } else {
      count += num * digits;
      num = 0;
    }
    digits++;
    current *= 10;
  }
  return count;
}

int main() {
  int64_t n;
  std::cin >> n;

  int64_t left = 1, right = 1e9;
  while (left < right) {
    int64_t mid = left + (right - left) / 2;
    if (count_digits(mid) < n) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  int64_t actual_number = left;
  int64_t total_digits = count_digits(actual_number - 1);
  int64_t position_in_number = n - total_digits - 1;
  std::string number_str = std::to_string(actual_number);
  char result = number_str[position_in_number];

  std::cout << result << '\n';

  return 0;
}

// Мое решение, если бы можно было поставить побольше -fconstexpr-depth
// #include <array>
// #include <iostream>

// constexpr size_t ARRAY_SIZE = 100'001;

// constexpr std::array<int, ARRAY_SIZE> create_array() {
//   std::array<int, ARRAY_SIZE> arr = {};
//   size_t index = 0;

//   for (size_t i = 0; i < ARRAY_SIZE; ++i) {
//     int temp = i;
//     int digits[6] = {};
//     size_t digit_count = 0;

//     while (temp > 0) {
//       digits[digit_count++] = temp % 10;
//       temp /= 10;
//     }

//     for (size_t i = digit_count; i > 0; --i) {
//       if (++index < ARRAY_SIZE) {
//         arr[index] = digits[i - 1];
//       }
//     }
//   }
//   return arr;
// }

// int main() {
//   constexpr auto arr = create_array();

//   size_t n = 0;
//   std::cin >> n;

//   std::cout << arr[n] << '\n';

//   return 0;
// }
