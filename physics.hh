#ifndef GUARD_physic_hh
#define GUARD_physic_hh

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "vector3d.hh"

#define G       6.67384e-11     // m^3 / (kg s^2)
#define GAUD    1.4880787e-34   // AU^3 / (kg day^2)
#define AU      1.49598e11      // m / AU

enum class Eclipse {
    NoEclipse, SolarEclipse, LunarEclipse
};

struct Body {
    double mass,                // kg
           radius;              // AU
    std::string name;

    Body(const double _m, const double _R, const std::string _n) :
        mass(_m), radius(_R / AU), name(_n) {}
};

struct System {
    std::vector<Body> bodies;
    std::vector<Vector3D> rs;   // AU
    std::vector<Vector3D> vs;   // AU / day
    double dt;                  // days (step time)

    System(double t) : dt(t) {}

    void add_body(const Body&, const Vector3D&, const Vector3D&);

    Eclipse pulse(void);
    Eclipse eclipse(void);

    std::string str() const;
    std::string str(bool) const;
    
    std::vector<Vector3D> accls(const std::vector<Vector3D>&) const;

    // Input/Output stream
    friend std::istream& operator>>(std::istream&, System&);
    friend std::ostream& operator<<(std::ostream&, const System&);
};

// Output stream
std::ostream& operator<<(std::ostream&, const System&);

Vector3D gravity(
	const Body&, const Vector3D&, const Body&, const Vector3D&);

#endif // GUARD
