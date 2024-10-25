#pragma once

#include <stdexcept>

class Date {
 private:
  int days_;

  static bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

  static int DaysInMonth(int month, int year) {
    switch (month) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      case 2:
        return IsLeapYear(year) ? 29 : 28;
      default:
        throw std::invalid_argument("Invalid month");
    }
  }

  static int DateToDays(int day, int month, int year) {
    int total_days = 0;
    for (int y = 1970; y < year; ++y) {
      total_days += IsLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
      total_days += DaysInMonth(m, year);
    }
    total_days += day - 1;
    return total_days;
  }

  void ValidateDate(int day, int month, int year) const {
    if (year < 1970 || year > 2099) {
      throw std::invalid_argument("Year must be between 1970 and 2099.");
    }
    if (month < 1 || month > 12) {
      throw std::invalid_argument("Month must be between 1 and 12.");
    }
    if (day < 1 || day > DaysInMonth(month, year)) {
      throw std::invalid_argument("Day is invalid for the given month and year.");
    }
  }

  void DaysToDate(int total_days, int& day, int& month, int& year) const {
    year = 1970;

    while (total_days >= (IsLeapYear(year) ? 366 : 365)) {
      total_days -= IsLeapYear(year) ? 366 : 365;
      ++year;
    }

    month = 1;
    while (total_days >= DaysInMonth(month, year)) {
      total_days -= DaysInMonth(month, year);
      ++month;
    }

    day = total_days + 1;
  }

 public:
  Date(int day, int month, int year) {
    ValidateDate(day, month, year);
    days_ = DateToDays(day, month, year);
  }

  Date(int day) : days_{day} {  // NOLINT
    ValidateDate(GetDay(), GetMonth(), GetYear());
  }

  int GetDay() const {
    int day, month, year;  // NOLINT
    DaysToDate(days_, day, month, year);
    return day;
  }

  int GetMonth() const {
    int day, month, year;  // NOLINT
    DaysToDate(days_, day, month, year);
    return month;
  }

  int GetYear() const {
    int day, month, year;  // NOLINT
    DaysToDate(days_, day, month, year);
    return year;
  }

  Date& operator++() {
    ++days_;
    return *this;
  }

  Date operator++(int) {
    Date tmp(*this);
    ++days_;
    return tmp;
  }

  Date& operator--() {
    --days_;
    return *this;
  }

  Date operator--(int) {
    Date tmp(*this);
    --days_;
    return tmp;
  }

  Date operator+(int days) const {
    return {days_ + days};
  }

  Date operator-(int days) const {
    return {days_ - days};
  }

  int operator-(const Date& other) const {
    return days_ - other.days_;
  }
};
