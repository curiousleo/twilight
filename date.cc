#include <iomanip>

#include "date.hh"

using namespace std;

// Days of the month. Attention: index must be month - 1.
const int DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int monthdays(const int year, const int month) {
    if (month == 2) // February
        return (year % 4 == 0 &&
            (year % 400 == 0) == (year % 100 == 0)) ?
                29 : 28;
    else
        return DAYS[month-1];
}

// Reset to UNIX time 0 :)
Date Date::reset() {
    year = 1970; month = 1; day = 1;
    return *this;
}

// Returns a bool indicating whether the given date is valid.
bool Date::valid() const {
    if (day < 0 || month < 0 || month > 12)
        return false;

    if (month == 2) // February
        return (day <= 28 ||
            (day == 29 && year % 4 == 0 &&
                (year % 400 == 0) == (year % 100 == 0)));
    else
        return (day <= DAYS[month-1]);
}

// String representation of our Date, used by operator <<
string Date::str() const {
    ostringstream s;
    int w = s.width(2);
    char f = s.fill('0');
    s << day << setw(1) << "/" << setw(2) << month << setw(1) << "/" << year;
    s.width(w);
    s.fill(f);
    return s.str();
}

// Equality test operator -- needed for hacky valid & validate functions
bool Date::operator==(Date _date) const {
    return (year == _date.year && month == _date.month && day == _date.day);
}

// Plus operator -- this is actually helpful.
// Adds integer 'days' given in argument (call by value) to the date.
Date Date::operator+(int days) const {
    Date date = *this;
    // ? : magic using the valid() function
    for (int i = 0; i != days; ++i) date++;
    return date;
}

// Unary Date += int operator: Just translate to +.
Date Date::operator+=(int days) {
    *this = *this + days;
    return *this;
}

// Unary Date++ operator: Just translate to += 1.
Date Date::operator++(int _) {
    Date _date = *this;
    Date date = Date(year, month, day+1);
    if (date.valid()) {
        *this = date;
        return _date;
    }
    date = Date(year, month+1, 1);
    if (date.valid()) {
        *this = date;
        return _date;
    }
    date = Date(year+1, 1, 1);
    *this = date;
    return _date;
}

// Unary ++Date operator: Just translate to Date++ and change Date.
Date Date::operator++() {
    return *this += 1;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.str();
    return os;
}
