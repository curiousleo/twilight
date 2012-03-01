// Twilight
//
// physics.hh
// Physical model of the constellation of sun, earth, and moon
//
// The classes Body and System provide a physical model of the
// constellation of sun, earth, and moon.

#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "geometry.hh"

/** The gravitational constant in m^3 / (kg s^2) */
#define G     6.67384e-11d
/** The gravitational constant in AU^3 / (kg day^2) */
#define GAUD  1.4880787e-34d
/** Metres per AU */
#define AU    1.49598e11d

/** Method of integration used to calculate velocities and positions. */
enum class IntegrationMethod
{
  Euler, Heun, Gauss, RK4, RKF
};

/** Describes the properties of a sperical body in space. */
struct Body
{
  double mass,        // kg
         radius;      // AU
  std::string name;

  Body (const double _mass, const double _radius, const std::string _name) :
    mass(_mass), radius(_radius / AU), name(_name) {}
};

/** The solar system. */
class System
{
 public:
  /** Constructor (no default constructor provided) */
  System (IntegrationMethod method, double dt) : method_(method), dt_(dt) {}

  Eigen::Array3Xd rs (void) { return rs_; }
  void update_rs (const Eigen::Array3Xd& rs) { rs_ += rs; }

  Eigen::Array3Xd vs (void) { return vs_; }
  void update_vs (const Eigen::Array3Xd& vs) { vs_ += vs; }

  IntegrationMethod method (void) { return method_; }

  double dt (void) { return dt_; }

  // Member methods
  void add_body (
      const Body body,
      const Eigen::Vector3d position,
      const Eigen::Vector3d velocity);
  Eclipse pulse (void);
  std::string str (void) const;
  Eigen::Array3Xd gravitate (const Eigen::Array3Xd& positions) const;

  // Input/Output stream
  friend std::istream& operator>> (std::istream& is, System& system);
  friend std::ostream& operator<< (std::ostream& os, const System& system);

 private:
  std::vector<Body> bodies_;

  /** Current positions of the system’s bodies in AUs. */
  Eigen::Array3Xd rs_;

  /** Current velocities of the system’s bodies in AUs per day. */
  Eigen::Array3Xd vs_;

  IntegrationMethod method_;

  /** Time step in days. */
  double dt_;
};

// Output stream
std::ostream&
operator<< (std::ostream& os, const System& system);

Eigen::Vector3d
gravity (
    const Body& body1, const Eigen::Vector3d& position1,
    const Body& body2, const Eigen::Vector3d& position2);

#endif // GUARD
