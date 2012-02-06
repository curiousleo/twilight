#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <iostream>
#include <vector>

#include <Eigen/Dense>

#define G     6.67384e-11d    // m^3 / (kg s^2)
#define GAUD  1.4880787e-34d  // AU^3 / (kg day^2)
#define AU    1.49598e11d     // m / AU

enum class Eclipse
{
  None, Solar, Lunar
};

enum class IntegrationMethod
{
  Euler, Heun, Gauss, RK4, RKF
};

struct Body
{
  double mass,        // kg
         radius;        // AU
  std::string name;

  Body (const double _m, const double _R, const std::string _n) :
    mass(_m), radius(_R / AU), name(_n) {}
};

class System
{
 public:
  // Initializers
  System (IntegrationMethod method, double dt) : method_(method), dt_(dt) {}

  // Getters and Setters
  Eigen::Array3Xd rs (void) { return rs_; }
  void update_rs (const Eigen::Array3Xd& rs) { rs_ += rs; }

  Eigen::Array3Xd vs (void) { return vs_; }
  void update_vs (const Eigen::Array3Xd& vs) { vs_ += vs; }

  IntegrationMethod method (void) { return method_; }
  double dt (void) { return dt_; }

  // Member methods
  void add_body (const Body, const Eigen::Vector3d, const Eigen::Vector3d);

  Eclipse pulse (void);
  Eclipse eclipse (void);

  std::string str (void) const;
  std::string str (bool) const;
  
  Eigen::Array3Xd gravitate (const Eigen::Array3Xd&) const;

  // Input/Output stream
  friend std::istream& operator>> (std::istream&, System&);
  friend std::ostream& operator<< (std::ostream&, const System&);

 private:
  std::vector<Body> bodies_;

  Eigen::Array3Xd rs_;     // AU
  Eigen::Array3Xd vs_;     // AU / day

  IntegrationMethod method_;
  double dt_;              // days (step time)
};

// Output stream
std::ostream&
operator<< (std::ostream&, const System&);

Eigen::Vector3d
gravity (
    const Body&, const Eigen::Vector3d&,
    const Body&, const Eigen::Vector3d&);

#endif // GUARD
