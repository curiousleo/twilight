#include <libtwilight/libtwilight.hh>

#include "utils.hh"

using namespace std;

int
main (int ac, char* av[])
{
  unsigned int days;
  double dt;
  IntegrationMethod method;

  if (cmdopts(ac, av, days, method, dt) != 0)
    return 1;

  unsigned int i, planets,
               interval = floor(days / (dt * 1000.0));
  int lasteclipse = -1;
  Eclipse eclipse;
  Date start(2008, 1, 7);
  System system(method, dt);

  cin >> planets;
  for (i = 0; i != planets; i++)
    cin >> system;
  i = 0;

  for (double t = 0; t < (double)days; t += dt) {
    eclipse = system.pulse();

    if (eclipse == Eclipse::Solar && floor(t) != lasteclipse) {
      lasteclipse = floor(t);
      cerr << start + lasteclipse << endl;
    }

    if (++i == interval) {
      cout << system;
      i = 0;
    }
  }
  cerr << endl;

  return 0;
}
