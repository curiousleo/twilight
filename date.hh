#ifndef GUARD_date_hh
#define GUARD_date_hh

#include <iostream>

class Date
{
 public:
  // Constructor with year, month, day as arguments
  Date (const int y, const int m, const int d) :
    year_(y), month_(m), day_(d) {}

  int year (void) const { return year_; }
  void set_year (int year) { year_ = year; }

  int month (void) const { return month_; }
  void set_month (int month) { month_ = month; }

  int day (void) const { return day_; }
  void set_day (int day) { day_ = day; }

  // Default initialisation
  Date (void) { reset(); }

  // Reset to UNIX time 0 :)
  Date reset (void);

  // Returns a bool indicating whether the given date is valid.
  bool valid (void) const;

  // String representation of our Date, used by operator <<
  std::string str (void) const;

  // Operators
  bool operator == (const Date&) const;
  Date operator + (int) const;
  Date operator += (const int);
  
  // Output stream
  friend std::ostream& operator<< (std::ostream&, const Date&);

 private:
  int year_, month_, day_;
};

int monthdays (const int, const int);

#endif // GUARD
