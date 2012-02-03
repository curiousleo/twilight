#include <iostream>  // cout
#include <sstream>   // ostringstream class, needed for Date.str()

using namespace std;

// Days of the month. Attention: index must be month - 1.
const int DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// TYPES
struct Date {
   // Date consists of a year, a month, and a day.
   int year, month, day;

   // Constructor with year, month, day as arguments
   Date(int y, int m, int d) : year(y), month(m), day(d) {}

   // Default initialisation
   Date() { reset(); }

   // Reset to UNIX time 0 :)
   Date reset() {
      year = 1970; month = 1; day = 1;
      return *this;
   }

   // Returns a bool indicating whether the given date is valid.
   bool valid() {
      if (month == 2) // February
         return (day <= 28 ||
            (day == 29 && year % 4 == 0 &&
               (year % 400) == (year % 100) == 0));
      else
         return (day > 0 && month > 0 && month <= 12 && 
            day <= DAYS[month-1]);
   }

   // Returns a bool indication whether the given date is valid;
   // if it is not valid, it will be reset to a valid date.
   bool validate() {
      if (valid()) return true;
      reset(); return false;
   }

   // String representation of our Date, used by operator <<
   string str() {
      ostringstream s;
      s << day << "/" << month << "/" << year;
      return s.str();
   }

   // Equality test operator -- needed for hacky valid & validate functions
   bool operator ==(Date _date) {
      return (year == _date.year && month == _date.month && day == _date.day);
   }

   // Plus operator -- this is actually helpful.
   // Adds integer 'days' given in argument (call by value) to the date.
   Date operator +(int days) {
      Date date;
      // ? : magic using the valid() function
      return (date = Date(year, month, day+1)).valid() ?
         date : (date = Date(year, month+1, 1)).valid() ?
            date : Date(year+1, 1, 1);
   }

   // Unary Date += int operator: Just translate to +.
   Date operator +=(int days) {
      *this = *this + days;
      return *this;
   }

   // Unary Date++ operator: Just translate to += 1.
   Date operator ++(int day) {
      return *this + 1;
   }

   // Unary ++Date operator: Just translate to Date++ and change Date.
   Date operator ++() {
      return *this += 1;
   }
};
