#include <libtwilight/libtwilight.hh>

#include "utils.hh"

using namespace std;

int
main (int ac, char* av[])
{
  // Initialise variables to be set by command-line options
  unsigned int days;
  double dt;
  IntegrationMethod method;

  // Populate variables from command-line options or defaults
  if (cmdopts(ac, av, days, method, dt) != 0)
    // Exit on parsing error
    return 1;

  // interval: Number of iterations between the state of the system is
  // written to cout
  unsigned int i, planets,
               interval = floor(days / (dt * 1000.0));
  int lasteclipse = -1;
  Eclipse eclipse;
  Date start(2008, 1, 7);
  System system(method, dt);

  // planets: Number of planets to read in
  cin >> planets;
  for (i = 0; i != planets; i++)
    cin >> system;
  i = 0;

  // Main loop: Iterate over time
  for (double t = 0; t < (double)days; t += dt) {
    // Pulse: system calculates new state, returns the type of eclipse
    // that occurred (Eclipse::None or Eclipse::Solar)
    eclipse = system.pulse();

    // If an eclipse occurred and this is not the day of the last
    // eclipse, print it to cerr
    if (eclipse == Eclipse::Solar && floor(t) != lasteclipse) {
      lasteclipse = floor(t);
      cerr << start + lasteclipse << endl;
    }

    // Write state of the system to cout at interval "interval"
    if (++i == interval) {
      cout << system;
      i = 0;
    }
  }
  cerr << endl;

  return 0;
}
