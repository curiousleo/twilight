#include "physics.hh"

using namespace std;

// Calculates the force acting on body 2
Vector3D gravity(const Body& b1, const Body& b2) {
    Vector3D d = b1.r - b2.r;
    // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
    return GAUD * b1.mass * b2.mass * d.norm() / d.len2();
}

vector<Vector3D> System::rs() const {
    vector<Vector3D> rs;
    for (
	    vector<Body>::const_iterator it = bodies.begin();
	    it != bodies.end(); it++) {
	rs.push_back(it->r);
    }
    return rs;
}

vector<Vector3D> System::vs() const {
    vector<Vector3D> vs;
    for (
	    vector<Body>::const_iterator it = bodies.begin();
	    it != bodies.end(); it++) {
	vs.push_back(it->v);
    }
    return vs;
}

// Return updated state of the system
vector<Vector3D> System::as(
	const vector<Vector3D>& rs, const vector<Vector3D>& vs, double dt) const {
    vector<Vector3D> as;
    vector<Body> _bodies = bodies;
    Vector3D f2;

    vector<Body>::iterator b_it1, b_it2;
    vector<Vector3D>::const_iterator r_it, v_it;

    for (
	    b_it1 = _bodies.begin(), r_it = rs.begin(), v_it = vs.begin();
	    b_it1 != _bodies.end() && r_it != rs.end() && v_it != vs.end();
	    b_it1++, r_it++, v_it++) {
	b_it1->r = *r_it;
	b_it1->v = *v_it;
    }
    for (b_it1 = _bodies.begin(); b_it1 != _bodies.end(); b_it1++) {
        // Reset acceleration
        b_it1->a = Vector3D();

        for (b_it2 = _bodies.begin(); b_it2 != _bodies.end(); b_it2++) {
            // Only calculate gravb_ity force for distinct bodies
            if (b_it1 == b_it2) continue;

            // Force acting on body 2
            f2 = gravity(*b_it1, *b_it2);
            b_it1->a += -f2 / b_it1->mass;
            b_it2->a +=  f2 / b_it2->mass;
        }
    }
    for (b_it1 = _bodies.begin(); b_it1 != _bodies.end(); b_it1++) {
	as.push_back(b_it1->a);
    }
    return as;
}

// Update positions
bool System::pulse(void) {
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
    a1 = as(r1, v1, 0);

    for (j = 0; j != i; j++) {
	r2.push_back(r1[j] + v1[j] * 0.5 * dt);
	v2.push_back(v1[j] + a1[j] * 0.5 * dt);
    }
    a2 = as(r2, v2, dt/2);

    for (j = 0; j != i; j++) {
	r3.push_back(r1[j] + v2[j] * 0.5 * dt);
	v3.push_back(v1[j] + a2[j] * 0.5 * dt);
    }
    a3 = as(r3, v3, dt/2);

    for (j = 0; j != i; j++) {
	r4.push_back(r1[j] + v3[j] * dt);
	v4.push_back(v1[j] + a3[j] * dt);
    }
    a4 = as(r4, v4, dt);

    // Update this System with the weightened average values for r, v, a
    for (j = 0; j != i; j++) {
	bodies[j].r += (dt/6) * (v1[j] + 2 * (v2[j] + v3[j]) + v4[j]);
	bodies[j].v += (dt/6) * (a1[j] + 2 * (a2[j] + a3[j]) + a4[j]);
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
}
std::ostream& operator<<(std::ostream& os, const System& s) {
    os << s.str();
    return os;
}
