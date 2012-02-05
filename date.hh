#ifndef GUARD_date_hh
#define GUARD_date_hh

#include <iostream>

class Date
{
 public:
  // Constructor with year, month, day as arguments
  Date (const int y, const int m, const int d) :
  year(y), month(m), day(d) {}

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
  Date operator ++ (const int);
  Date operator ++ (void);
  
  // Output stream
  friend std::ostream& operator<< (std::ostream&, const Date&);

 private:
  int year, month, day;
};

int monthdays (const int, const int);

#endif // GUARD
