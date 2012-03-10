// Twilight
//
// physics.cc
// Physical model of the constellation of sun, earth, and moon

#include <sstream>

#include "numerics.hh"
#include "physics.hh"

using namespace std;
using namespace Eigen;

/** Calculate the gravitational force exerted by body 2 on body 1. */
Vector3d
gravity (
    const Body& body1, const Vector3d& position1,
    const Body& body2, const Vector3d& position2)
{
  Vector3d d = position2 - position1;
  return d.normalized() * GAUD * body1.mass * body2.mass / d.squaredNorm();
}

/**
 * Return an Array containing the gravitational acceleration of each
 * body in a system due to all other bodies in the system.
 * \param positions Array of the current positions of the bodies
 */
Array3Xd
System::gravitate (const Array3Xd& positions) const
{
  const vector<Body>::size_type n = bodies_.size();
  vector<Body>::size_type i, j;
  Array3Xd as_tmp = Array3Xd::Zero(3, rs_.matrix().rows());
  Vector3d f;

  for (i = 0; i != (n - 1); ++i) {
    Body b1 = bodies_[i];

    for (j = i + 1; j != n; ++j) {
      Body b2 = bodies_[j];

      // Force acting on body 1
      f = gravity(b1, positions.col(i), b2, positions.col(j));
      as_tmp.col(i) += f.array() / b1.mass;
      as_tmp.col(j) -= f.array() / b2.mass;
    }
  }
  return as_tmp;
}

/** Advance the state of the system by one time step. */
Eclipse
System::pulse (void)
{
  switch (method_) {
	case IntegrationMethod::Euler: euler(this); break;
	case IntegrationMethod::Heun:  heun(this);  break;
	case IntegrationMethod::Gauss: gauss(this); break;
	case IntegrationMethod::RK4:   rk4(this);   break;
	case IntegrationMethod::RKF:   rkf(this);   break;
  }

  const double moon_radius = bodies_[0].radius,
               earth_radius = bodies_[1].radius,
               sun_radius = bodies_[2].radius;
  const Vector3d moon = rs_.col(0),
                 earth = rs_.col(1),
                 sun = rs_.col(2);

  if (eclipse(
        moon, moon_radius, earth, earth_radius, sun, sun_radius))
    return Eclipse::Solar;
  else
    return Eclipse::None;
}

/** Add a body to the system. */
void
System::add_body (
	const Body body, const Vector3d position, const Vector3d velocity)
{
  bodies_.push_back(body);

  rs_.conservativeResize(NoChange, rs_.cols() + 1);
  rs_.rightCols<1>() = position;

  vs_.conservativeResize(NoChange, vs_.cols() + 1);
  vs_.rightCols<1>() = velocity;
}

/** Return string representation for the system. */
string
System::str (void) const
{
  ostringstream os;
  vector<Body>::size_type n = bodies_.size(), i;
  os << n << endl;

  for(i = 0; i != n; ++i)
    os << rs_.col(i).row(0) << " " << rs_.col(i).row(1) << " "
      << 1 /* bodies_[i].mass */ << endl;
  return os.str();
}

/** Read a body from an input stream and add it to the system. */
std::istream&
operator>> (std::istream& is, System& system)
{
  string name;
  double rx, ry, rz, vx, vy, vz, m, R;

  is >> name >> rx >> ry >> rz >> vx >> vy >> vz >> m >> R;
  system.add_body(
      Body(m, R, name),
      Vector3d(rx, ry, rz), Vector3d(vx, vy, vz));
  return is;
}

/** Print the system’s string representation to an output stream. */
std::ostream&
operator<< (std::ostream& os, const System& system)
{
  os << system.str();
  return os;
}
