#ifndef GUARD_physic_hh
#define GUARD_physic_hh

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "vector3d.hh"

struct Body {
    double mass;
    Vector3D r, v, a;

    Body(const Vector3D& _r, const Vector3D& _v, const double _m) :
        r(_r), v(_v), mass(_m) {}
};

struct System {
    std::vector<Body> bodies;
    double dt;

    System(std::vector<Body> b, double t) : bodies(b), dt(t) {}

    bool pulse(void);
    std::string str() const;
    std::string str(bool) const;
    
    // Input/Output stream
    friend std::ostream& operator<<(std::ostream&, const System&);
};

// Output stream
std::ostream& operator<<(std::ostream&, const System&);

Vector3D gravity(const Body&, const Body&);

#endif // GUARD
