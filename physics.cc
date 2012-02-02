#include <functional>

#include "numerics.hh"
#include "physics.hh"

using namespace std;

// Calculates the force acting on body 1
inline Vector3D gravity(
        const Body& b1, const Vector3D& r1,
        const Body& b2, const Vector3D& r2) {
    Vector3D d = r2 - r1;
    // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
    return GAUD * b1.mass * b2.mass * d.norm() / d.len2();
}

// Return updated state of the system
vector<Vector3D> System::gravitate(const vector<Vector3D>& tmp_rs) const {
    const vector<Body>::size_type n = bodies.size();
    vector<Body>::size_type i, j;
    vector<Vector3D> tmp_as(n);
    Vector3D f;

    for (i = 0; i != (n - 1); ++i) {
        Body b1 = bodies[i];

        for (j = i + 1; j != n; ++j) {
            Body b2 = bodies[j];

            // Force acting on body 1
            f = gravity(b1, tmp_rs[i], b2, tmp_rs[j]);
            tmp_as[i] += f / b1.mass;
            tmp_as[j] -= f / b2.mass;
        }
    }
    return tmp_as;
}

// Update positions
Eclipse System::pulse(void) {
    rk4(rs, vs, dt, gravitate);

    return eclipse();
}

// Check if we're having a solar eclipse
Eclipse System::eclipse(void) {
    // Check alignment
    // Assuming the order of celestial bodies in vector bodies is Moon,
    // Earth, Sun
    Vector3D SM = rs[0] - rs[2]; // Sun->Moon
    Vector3D SE = rs[1] - rs[2]; // Sun->Earth

    double costheta = SM * SE / sqrt(SM.len2() * SE.len2());
    double eta      = asin(bodies[1].radius / SE.len());
    return abs(costheta) > cos(eta) ?
        Eclipse::SolarEclipse : Eclipse::NoEclipse;
}

// Add a body
void System::add_body(
        const Body& body, const Vector3D& r, const Vector3D& v) {
    bodies.push_back(body);
    rs.push_back(r);
    vs.push_back(v);
}

// String formatter
string System::str(void) const { return str(false); }
string System::str(bool verbose) const {
    ostringstream os;
    vector<Body>::size_type n = bodies.size(), i;
    os << n << endl;

    for(i = 0; i != n; ++i)
        os << rs[i].x << " " << rs[i].y << " "
            << 1 /* bodies[i].mass */ << endl;
    return os.str();
}

// Input/Output stream
std::istream& operator>>(std::istream& is, System& s) {
    string name;
    double rx, ry, rz, vx, vy, vz, m, R;

    is >> name >> rx >> ry >> rz >> vx >> vy >> vz >> m >> R;
    s.add_body(
            Body(m, R, name),
            Vector3D(rx, ry, rz), Vector3D(vx, vy, vz));
    return is;
}
std::ostream& operator<<(std::ostream& os, const System& s) {
    os << s.str();
    return os;
}
