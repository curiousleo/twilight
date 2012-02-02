#include "physics.hh"

using namespace std;

// Calculates the force acting on body 1
Vector3D gravity(
	const Body& b1, const Vector3D& r1,
	const Body& b2, const Vector3D& r2) {
    Vector3D d = r2 - r1;
    // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
    return GAUD * b1.mass * b2.mass * d.norm() / d.len2();
}

// Return updated state of the system
vector<Vector3D> System::accls(const vector<Vector3D>& tmp_rs) const {
    vector<Vector3D> tmp_as;
    Vector3D a, f;
    int i = 0, j = 0;

    vector<Body>::const_iterator b_it1, b_it2;

    for (b_it1 = bodies.begin(); b_it1 != bodies.end(); b_it1++) {
        // Reset acceleration
	a = Vector3D();

        for (b_it2 = bodies.begin(); b_it2 != bodies.end(); b_it2++) {
            // Only calculate gravity force for distinct bodies
            if (b_it1 == b_it2) {
		++j;
		continue;
	    }

            // Force acting on body 1
            f = gravity(*b_it1, tmp_rs[i], *b_it2, tmp_rs[j]);
            a += f / b_it1->mass;

	    ++j;
        }
	tmp_as.push_back(a);
	++i;
    }
    return tmp_as;
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

    vector<Vector3D> r1(rs), v1(vs), a1,
                     r2, v2, a2,
                     r3, v3, a3,
                     r4, v4, a4;

    static long long k = 0;
    // if (k == 0) cerr << rs[0] << rs[1] << rs[2];
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
        rs[j] += (dt/6) * (v1[j] + 2 * (v2[j] + v3[j]) + v4[j]);
        vs[j] += (dt/6) * (a1[j] + 2 * (a2[j] + a3[j]) + a4[j]);
    }
    // return abs(costheta) > cos(0.01);
    // return (1 - abs(costheta)) < 9.336e-10;
    k++;
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

// Add a body to the system
void System::add_body(const Body& body, const Vector3D& r, const Vector3D& v) {
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

    for (i = 0; i != n; ++i) {
        os << rs[i].x << " " << rs[i].y << " " << 1 << endl;
    }
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
