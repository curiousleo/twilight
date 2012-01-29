#include "vector3d.hh"
#include "physics.hh"

using namespace std;

int main(void) {
    unsigned int i;
    double dt = 0.01;	// days
    int lasteclipse = -1;
    System s(dt);

    cin >> i;
    for (unsigned int j = 0; j != i; j++) {
        cin >> s;
    }

    int w = 0;
    for (double t = 0; t < 360 * 5; t += dt) {
	if (s.pulse() && floor(t) != lasteclipse) {
	    lasteclipse = floor(t);
	    cerr << lasteclipse << " ";
	}
	if (w++ == 80) {
	    cout << s;
	    w = 0;
	}
    }
    return 0;
}
