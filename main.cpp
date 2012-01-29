#include "vector3d.hh"
#include "physics.hh"

using namespace std;

int main(void) {
    unsigned int i;
    double dt = 0.1;	// days
    int lasteclipse = -1;
    System s(dt);

    cin >> i;
    for (unsigned int j = 0; j != i; j++) {
        cin >> s;
    }

    for (double t = 0; t < 360; t += dt) {
	s.pulse();
	cout << s;
    }
    return 0;
}
