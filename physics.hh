#ifndef GUARD_physic_hh
#define GUARD_physic_hh

#include <iostream>
#include <sstream>
#include <vector>

#include "vector3d.hh"

#define G  6.67300e-11 // m^3 / (kg s^2)
#define AU 1.49598e11  // m / AU

struct Body {
    double mass, radius;
    Vector3D r, v, a;
    std::string name;

    Body(
            const Vector3D& _r, const Vector3D& _v,
            const double _m, const double _R, const std::string _n) :
        r(_r), v(_v), mass(_m), radius(_R), name(_n) {}
};

struct System {
    std::vector<Body> bodies;
    double dt;

    System() {}
    System(std::vector<Body> b, double t) : bodies(b), dt(t) {}

    bool pulse(void);
    std::string str() const;
    std::string str(bool) const;
    
    // Input/Output stream
    friend std::istream& operator>>(std::istream&, System&);
    friend std::ostream& operator<<(std::ostream&, const System&);
};

// Output stream
std::ostream& operator<<(std::ostream&, const System&);

Vector3D gravity(const Body&, const Body&);

#endif // GUARD
