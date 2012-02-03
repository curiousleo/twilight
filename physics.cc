#include "numerics.hh"
#include "physics.hh"

using namespace std;
using namespace Eigen;

// Calculates the force acting on body 1
inline Vector3d gravity(
        const Body& b1, const Vector3d& r1,
        const Body& b2, const Vector3d& r2) {
    Vector3d d = r2 - r1;
    // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
    return d.normalized() * GAUD * b1.mass * b2.mass / d.squaredNorm();
    /*
    // Alternatively:
    double len = d.norm();
    double c = GAUD * b1.mass * b2.mass / (len * len * len);
    return Vector3d(c * d[0], c * d[1], c * d[2]);
    */
}

// Return updated state of the system
Array3Xd System::gravitate(const Array3Xd& tmp_rs) const {
    const vector<Body>::size_type n = bodies.size();
    vector<Body>::size_type i, j;
    Array3Xd as_tmp;
    as_tmp.resize(NoChange, rs.matrix().rows());
    Vector3d f;

    for (i = 0; i != (n - 1); ++i) {
        Body b1 = bodies[i];

        for (j = i + 1; j != n; ++j) {
            Body b2 = bodies[j];

            // Force acting on body 1
            f = gravity(b1, tmp_rs.col(i), b2, tmp_rs.col(j));
            as_tmp.col(i) += f.array() / b1.mass;
            as_tmp.col(j) -= f.array() / b2.mass;
        }
    }
    return as_tmp;
}

// Update positions
Eclipse System::pulse(void) {
    rk4(this);
    return eclipse();
}

// Check if we're having a solar eclipse
Eclipse System::eclipse(void) {
    // Check alignment
    // Assuming the order of celestial bodies in vector bodies is Moon,
    // Earth, Sun
    Vector3d SM = rs.col(0) - rs.col(2); // Sun->Moon
    Vector3d SE = rs.col(1) - rs.col(2); // Sun->Earth

    double costheta = SM.dot(SE) / sqrt(SM.squaredNorm() * SE.squaredNorm());
    double eta      = asin(bodies[1].radius / SE.norm());
    return abs(costheta) > cos(eta) ?
        Eclipse::SolarEclipse : Eclipse::NoEclipse;
}

// Add a body
void System::add_body(
        const Body body, const Vector3d r, const Vector3d v) {
    bodies.push_back(body);

    rs.conservativeResize(NoChange, rs.cols() + 1);
    rs.rightCols<1>() = r;

    vs.conservativeResize(NoChange, vs.cols() + 1);
    vs.rightCols<1>() = v;
}

// String formatter
string System::str(void) const { return str(false); }
string System::str(bool verbose) const {
    ostringstream os;
    vector<Body>::size_type n = bodies.size(), i;
    os << n << endl;

    for(i = 0; i != n; ++i)
        os << rs.row(i).col(0) << " " << rs.row(i).col(1) << " "
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
            Vector3d(rx, ry, rz), Vector3d(vx, vy, vz));
    return is;
}
std::ostream& operator<<(std::ostream& os, const System& s) {
    os << s.str();
    return os;
}
