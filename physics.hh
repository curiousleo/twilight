#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <iostream>
#include <sstream>
#include <vector>

#include <Eigen/Dense>

#define G       6.67384e-11d    // m^3 / (kg s^2)
#define GAUD    1.4880787e-34d  // AU^3 / (kg day^2)
#define AU      1.49598e11d     // m / AU

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
    std::vector<Eigen::Vector3d> rs;   // AU
    std::vector<Eigen::Vector3d> vs;   // AU / day
    double dt;                  // days (step time)

    System(double t) : dt(t) {}

    void add_body(const Body, const Eigen::Vector3d, const Eigen::Vector3d);

    Eclipse pulse(void);
    Eclipse eclipse(void);

    std::string str() const;
    std::string str(bool) const;
    
    std::vector<Eigen::Vector3d> gravitate(const std::vector<Eigen::Vector3d>&) const;

    // Input/Output stream
    friend std::istream& operator>>(std::istream&, System&);
    friend std::ostream& operator<<(std::ostream&, const System&);
};

// Output stream
std::ostream& operator<<(std::ostream&, const System&);

Eigen::Vector3d gravity(
	const Body&, const Eigen::Vector3d&, const Body&, const Eigen::Vector3d&);

#endif // GUARD
