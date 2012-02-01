#include "physics.hh"

using namespace std;

// Calculates the force acting on body 1
Vector3D gravity(const Body& b1, const Body& b2) {
    Vector3D d = b2.r - b1.r;
    // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
    return GAUD * b1.mass * b2.mass * d.norm() / d.len2();
}

vector<Vector3D> System::rs() const {
    vector<Vector3D> rs;
    for(const Body& body : bodies) { rs.push_back(body.r); }
    return rs;
}

vector<Vector3D> System::vs() const {
    vector<Vector3D> vs;
    for(const Body& body : bodies) { vs.push_back(body.v); }
    return vs;
}

// Return updated state of the system
vector<Vector3D> System::accls(const vector<Vector3D>& rs) const {
    vector<Vector3D> as;
    vector<Body> _bodies = bodies;
    Vector3D f;

    vector<Body>::iterator b_it1, b_it2;
    vector<Vector3D>::const_iterator r_it, v_it;

    for (
        b_it1 = _bodies.begin(), r_it = rs.begin();
        b_it1 != _bodies.end() && r_it != rs.end();
        b_it1++, r_it++) {
    b_it1->r = *r_it;
    }
    for (b_it1 = _bodies.begin(); b_it1 != _bodies.end(); b_it1++) {
        // Reset acceleration
        b_it1->a = Vector3D();

        for (b_it2 = _bodies.begin(); b_it2 != _bodies.end(); b_it2++) {
            // Only calculate gravity force for distinct bodies
            if (b_it1 == b_it2) continue;

            // Force acting on body 1
            f = gravity(*b_it1, *b_it2);
            b_it1->a += f / b_it1->mass;
        }
    }
    for (b_it1 = _bodies.begin(); b_it1 != _bodies.end(); b_it1++) {
    as.push_back(b_it1->a);
    }
    return as;
}

// Update positions
Eclipse System::pulse(void) {
    /*
    x1 = x
    v1 = v
    a1 = a(x1, v1, 0)

    x2 = x + 0.5*v1*dt
    v2 = v + 0.5*a1*dt
    a2 = a(x2, v2, dt/2.0)

    x3 = x + 0.5*v2*dt
    v3 = v + 0.5*a2*dt
    a3 = a(x3, v3, dt/2.0)

    x4 = x + v3*dt
    v4 = v + a3*dt
    a4 = a(x4, v4, dt)

    xf = x + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4)
    vf = v + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4)
    */
    const vector<Body>::size_type i = bodies.size();
    vector<Body>::size_type j;

    vector<Vector3D> r1, v1, a1,
                     r2, v2, a2,
                     r3, v3, a3,
                     r4, v4, a4;
    vector<Vector3D>::iterator r_it, v_it, a_it;

    r1 = rs();
    v1 = vs();
    a1 = accls(r1);

    for (j = 0; j != i; j++) {
        r2.push_back(r1[j] + v1[j] * 0.5 * dt);
        v2.push_back(v1[j] + a1[j] * 0.5 * dt);
    }
    a2 = accls(r2);

    for (j = 0; j != i; j++) {
        r3.push_back(r1[j] + v2[j] * 0.5 * dt);
        v3.push_back(v1[j] + a2[j] * 0.5 * dt);
    }
    a3 = accls(r3);

    for (j = 0; j != i; j++) {
        r4.push_back(r1[j] + v3[j] * dt);
        v4.push_back(v1[j] + a3[j] * dt);
    }
    a4 = accls(r4);

    // Update this System with the weightened average values for r, v, a
    for (j = 0; j != i; j++) {
        bodies[j].r += (dt/6) * (v1[j] + 2 * (v2[j] + v3[j]) + v4[j]);
        bodies[j].v += (dt/6) * (a1[j] + 2 * (a2[j] + a3[j]) + a4[j]);
    }
    // return abs(costheta) > cos(0.01);
    // return (1 - abs(costheta)) < 9.336e-10;
    return eclipse();
}

// Check if we're having a solar eclipse
Eclipse System::eclipse(void) {
    // Check alignment
    // Assuming the order of celestial bodies in vector bodies is Moon,
    // Earth, Sun
    Vector3D SM = bodies[0].r - bodies[2].r; // Sun->Moon
    Vector3D SE = bodies[1].r - bodies[2].r; // Sun->Earth

    double costheta = SM * SE / sqrt(SM.len2() * SE.len2());
    double eta      = asin(bodies[1].radius / SE.len());
    return abs(costheta) > cos(eta) ?
        Eclipse::SolarEclipse : Eclipse::NoEclipse;
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
        os << it->r.x << " " << it->r.y << " " << 1 << endl;
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
    return is;
}
std::ostream& operator<<(std::ostream& os, const System& s) {
    os << s.str();
    return os;
}
