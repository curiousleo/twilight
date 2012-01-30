#ifndef GUARD_physic_hh
#define GUARD_physic_hh

#include <iostream>
#include <sstream>
#include <vector>

#include "vector3d.hh"

#define G	6.67384e-11     // m^3 / (kg s^2)
#define GAUD	1.4880787e-34   // AU^3 / (kg day^2)
#define AU	1.49598e11      // m / AU

enum SolarEclipse {
    NoSolarEclipse, PartialSolarEclipse, TotalSolarEclipse
};

struct Body {
    double mass,                // kg
           radius;              // AU
    Vector3D r,                 // AU (vector)
             v,                 // AU / day (vector)
             a;                 // AU / day^2 (vector)
    std::string name;

    Body(
            const Vector3D& _r, const Vector3D& _v,
            const double _m, const double _R, const std::string _n) :
        r(_r), v(_v), mass(_m), radius(_R / AU), name(_n) {}
};

struct System {
    std::vector<Body> bodies;
    double dt;                  // days (step time)

    System(double t) : dt(t) {}
    System(std::vector<Body> b, double t) : bodies(b), dt(t) {}

    SolarEclipse pulse(void);
    SolarEclipse eclipse(void);

    std::string str() const;
    std::string str(bool) const;
    
    std::vector<Vector3D> rs(void) const;
    std::vector<Vector3D> vs(void) const;
    std::vector<Vector3D> as(
	    const std::vector<Vector3D>&, const std::vector<Vector3D>&,
	    double) const;

    // Input/Output stream
    friend std::istream& operator>>(std::istream&, System&);
    friend std::ostream& operator<<(std::ostream&, const System&);
};

// Output stream
std::ostream& operator<<(std::ostream&, const System&);

Vector3D gravity(const Body&, const Body&);

#endif // GUARD
