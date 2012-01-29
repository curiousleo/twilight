#include "vector3d.hh"
#include "physics.hh"

using namespace std;

int main(void) {
    unsigned int i;
    double dt = 0.001;	// days
    int lasteclipse = -1;
    System s(dt);

    cin >> i;
    for (unsigned int j = 0; j != i; j++) {
        cin >> s;
    }

    for (double t = 0; t < 10000; t += dt) {
        if (s.pulse() && floor(t) != lasteclipse) {
	    lasteclipse = floor(t);
	    cerr << t+dt << " ";
	}
        // cout << s;
    }
    cerr << endl;
    return 0;
}
