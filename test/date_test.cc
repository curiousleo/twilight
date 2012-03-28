#include <iostream>

#include <libtwilight/date.hh>

using namespace std;

int
main (int ac, char* av[])
{
  Date start(2008, 1, 7);
  int add;
  
  while (true) {
    cin >> add;
    cout << start + add << endl;
  }

  return 0;
}
