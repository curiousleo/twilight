#include "physics.hh"

using namespace std;

// Calculates the force acting on body 2
Vector3D gravity(const Body& b1, const Body& b2) {
    Vector3D d = b1.r - b2.r;
    return G * b1.mass * b2.mass * d / (pow(d.len(), 3) * AU * AU);
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
    // Assuming the order of celestial bodies in vector bodies is Moon,
    // Earth, Sun
    Vector3D SM = bodies[0].r - bodies[2].r; // Sun->Earth
    Vector3D SE = bodies[1].r - bodies[2].r; // Sun->Moon

    double costheta = SM * SE / sqrt(SM.len2() * SE.len2());
    // return abs(costheta) > cos(0.01);
    return (1 - abs(costheta)) < (1 - cos(0.01));
}

// String formatter
string System::str(void) const { return str(false); }
string System::str(bool verbose) const {
    ostringstream os;
    os << bodies.size() << endl;

    for (
            vector<Body>::const_iterator it = bodies.begin();
            it != bodies.end(); it++) {
        os << it->r << " " << it->v << " " << it->a
            << " " << it->mass << endl;
    }
    return os.str();
}

// Input/Output stream
std::istream& operator>>(std::istream& is, System& s) {
    string name;
    double rx, ry, rz, vx, vy, vz, m, R;

    is >> name >> rx >> ry >> rz >> vx >> vy >> vz >> m >> R;
    s.bodies.push_back(Body(
                Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m, R, name));
}
std::ostream& operator<<(std::ostream& os, const System& s) {
    os << s.str();
    return os;
}
