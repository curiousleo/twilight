// Twilight
//
// date.hh
// Date class definition
//
// Date - a simple Gregorian calendar date class.

#ifndef GUARD_date_hh
#define GUARD_date_hh

#include <iostream>

/** Simple Gregorian calendar date class. */
class Date
{
 public:
  /** Default constructor */
  Date (void) : year_(1970), month_(1), day_(1) {}

  /** Constructor with year, month, day as arguments */
  Date (const int y, const int m, const int d) :
    year_(y), month_(m), day_(d) {}

  int year (void) const { return year_; }
  void set_year (int year) { year_ = year; }

  int month (void) const { return month_; }
  void set_month (int month) { month_ = month; }

  int day (void) const { return day_; }
  void set_day (int day) { day_ = day; }

  std::string str (void) const;

  // Operators
  Date operator + (int) const;
  
  // Output stream
  friend std::ostream& operator<< (std::ostream&, const Date&);

 private:
  int year_, month_, day_;
};

int monthdays (const int, const int);

#endif // GUARD
