#ifndef GUARD_date_hh
#define GUARD_date_hh

#include <iostream>   // cout
#include <sstream>    // ostd::stringstream class, needed for Date.str()

struct Date {
    // Date consists of a year, a month, and a day.
    int year, month, day;

    // Constructor with year, month, day as arguments
    Date(const int y, const int m, const int d) :
            year(y), month(m), day(d) {}

    // Default initialisation
    Date() { reset(); }

    // Reset to UNIX time 0 :)
    Date reset();

    // Returns a bool indicating whether the given date is valid.
    bool valid() const;

    // String representation of our Date, used by operator <<
    std::string str() const;

    // Operators
    bool operator ==(Date _date) const;
    Date operator +(int days) const;
    Date operator +=(int days);
    Date operator ++(int day);
    Date operator ++();
    
    // Output stream
    friend std::ostream& operator<<(std::ostream&, const Date&);
};

int monthdays(const int, const int);

#endif // GUARD
