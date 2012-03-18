// Twilight
//
// date.cc
// Date class implementation

#include <iomanip>
#include <sstream>

#include "date.hh"

using namespace std;

/** Days of the month. Attention: index must be month - 1. */
const int DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/** Return number of days in this month of this year. */
int
monthdays (const int year, const int month)
{
    if (month == 2) // February
        return (year % 4 == 0 &&
            (year % 400 == 0) == (year % 100 == 0)) ?
                29 : 28;
    else
        return DAYS[month-1];
}

/** String representation of Date, used by operator <<. */
string
Date::str (void) const
{
    ostringstream s;
    int w = s.width(2);
    char f = s.fill('0');
    s << day_ << setw(1) << "/" << setw(2) << month_ << setw(1) << "/" << year_;
    s.width(w);
    s.fill(f);
    return s.str();
}

/**
 * Plus operator. Increases the date by a number of days.
 *
 * \param days Number of days by which the date is increased
 */
Date
Date::operator+ (int days) const
{
    Date d = *this;
    int mdays;

    while (days != 0) {
	mdays = monthdays(d.year(), d.month());

	if (d.day() + days > mdays) {
      if (d.month() == 12) {
		d.set_year(d.year() + 1);
		d.set_month(1);
      }
      else
		d.set_month(d.month() + 1);

	    days -= mdays;
	}

	else {
	    d.set_day(d.day() + days);
	    break;
	}
    }

    return d;
}

/**
 * Output stream operator <<.
 *
 * \param os Output stream to write to
 * \param d  Date
 */
std::ostream&
operator<< (std::ostream& os, const Date& d)
{
  os << d.str();
  return os;
}

