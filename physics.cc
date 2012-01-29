#include "physics.hh"

using namespace std;

// Calculates the force acting on body 2
Vector3D gravity(const Body& b1, const Body& b2) {
    Vector3D d = b1.r - b2.r;
    return G * b1.mass * b2.mass * d / (pow(d.len(), 3) * AU * AU);
}

// Return updated state of the system
System System::step(double dt) const {
    System s = *this;
    vector<Body>::iterator it1, it2;
    Vector3D f2;

    for (it1 = s.bodies.begin(); it1 != s.bodies.end(); it1++) {
        // Reset acceleration
        it1->a = Vector3D();

        for (it2 = s.bodies.begin(); it2 != s.bodies.end(); it2++) {
            // Only calculate gravity force for distinct bodies
            if (it1 == it2) continue;

            // Force acting on body 2
            f2 = gravity(*it1, *it2);
            it1->a += -f2 / it1->mass;
            it2->a +=  f2 / it2->mass;
        }
    }

    for (it1 = s.bodies.begin(); it1 != s.bodies.end(); it1++) {
        // Euler integration
        it1->r += it1->v * dt;
        it1->v += it1->a * dt;
    }
    return s;
}

// Update positions
bool System::pulse(void) {
    vector<Body>::size_type i;

    System s1 = step(0);
    System s2 = s1.step(dt/2);
    System s3 = s2.step(dt/2);
    System s4 = s3.step(dt);

    // Update this System with the weightened average values for r, v, a
    // for all the bodies from s1 to s4
    for (i = 0; i != bodies.size(); i++) {
	bodies[i].r += (dt/6) * (s1.bodies[i].r + 2 * (s2.bodies[i].r + s3.bodies[i].r) + s4.bodies[i].r);
	bodies[i].v += (dt/6) * (s1.bodies[i].v + 2 * (s2.bodies[i].v + s3.bodies[i].v) + s4.bodies[i].v);
    }

    // Check alignment
    // Assuming the order of celestial bodies in vector bodies is Moon,
    // Earth, Sun
    Vector3D SM = bodies[0].r - bodies[2].r; // Sun->Earth
    Vector3D SE = bodies[1].r - bodies[2].r; // Sun->Moon

    double costheta = SM * SE / sqrt(SM.len2() * SE.len2());
    // return abs(costheta) > cos(0.01);
    return (1 - abs(costheta)) < (1 - cos(0.005));
}

// String formatter
string System::str(void) const { return str(false); }
string System::str(bool verbose) const {
    ostringstream os;
    os << bodies.size() << endl;

    for (
            vector<Body>::const_iterator it = bodies.begin();
            it != bodies.end(); it++) {
        // os << it->r << " " << it->v << " " << it->a
            // << " " << it->mass << endl;
	// z-face
        os << it->r.x << " " << it->r.y << " " << 1e7 << endl;
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
