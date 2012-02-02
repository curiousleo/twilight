#include "physics.hh"

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main(void) {
    unsigned int i;
    double dt = 0.001;  // days
    int lasteclipse = -1;
    System s(dt);

    cin >> i;
    for (unsigned int j = 0; j != i; j++) {
        cin >> s;
    }

    int w = 0;
    for (double t = 0; t < 2490; t += dt) {
        if (s.pulse() != Eclipse::NoEclipse && floor(t) != lasteclipse) {
            lasteclipse = floor(t);
            cerr << lasteclipse << " ";
        }
        if (w++ == 800) {
            cout << s;
            w = 0;
        }
    }
    cerr << endl;
    return 0;
}
