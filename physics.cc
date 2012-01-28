#include "physics.hh"

using namespace std;

// Calculates the force acting on body 2
Vector3D gravity(const Body& b1, const Body& b2) {
    Vector3D d = b1.r - b2.r;
    return b1.mass * b2.mass * d / pow(d.len(), 3);
}

// Update positions
bool System::pulse(void) {
    vector<Body>::iterator it1, it2;
    Vector3D f2;
    double theta;

    for (it1 = bodies.begin(); it1 != bodies.end(); it1++) {
        // Reset acceleration
        it1->a = Vector3D();

        for (it2 = bodies.begin(); it2 != bodies.end(); it2++) {
            // Only calculate gravity force for distinct bodies
            if (it1 == it2) continue;

            // Force acting on body 2
            f2 = gravity(*it1, *it2);
            it1->a += -f2 / it1->mass;
            it2->a +=  f2 / it2->mass;
        }
    }

    for (it1 = bodies.begin(); it1 != bodies.end(); it1++) {
        // Euler integration
        it1->r += it1->v * dt;
        it1->v += it1->a * dt;
    }

    // Check alignment
    // theta = arg(bodies[2].r - bodies[0].r) - arg(bodies[1].r - bodies[0].r);
    // return (1 - abs(cos(theta))) < (1 - cos(0.01));
    return false;
}

// String formatter
string System::str(void) { return str(false); }
string System::str(bool verbose) {
    ostringstream os;
    os << bodies.size() << endl;

    for (
            vector<Body>::const_iterator it = bodies.begin();
            it != bodies.end(); it++) {
        if (verbose)
            os << it->r << " " << it->v << " " << it->a
                << " " << it->mass << endl;
        // else
            // os << real(it->r) << " " << imag(it->r) << " " << it->mass << endl;
    }
    return os.str();
}
