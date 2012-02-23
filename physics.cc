#include <sstream>

#include "numerics.hh"
#include "physics.hh"

using namespace std;
using namespace Eigen;

// Calculates the force acting on body 1
inline Vector3d
gravity (
    const Body& b1, const Vector3d& r1,
    const Body& b2, const Vector3d& r2)
{
  Vector3d d = r2 - r1;
  // Units: (AU^3 / (kg day^2)) * kg^2 / AU^2 = kg AU / day^2
  return d.normalized() * GAUD * b1.mass * b2.mass / d.squaredNorm();
}

// Return updated state of the system
Array3Xd
System::gravitate (const Array3Xd& tmp_rs) const
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
      f = gravity(b1, tmp_rs.col(i), b2, tmp_rs.col(j));
      as_tmp.col(i) += f.array() / b1.mass;
      as_tmp.col(j) -= f.array() / b2.mass;
    }
  }
  return as_tmp;
}

// Update positions
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
  else if (eclipse(
        earth, earth_radius, moon, moon_radius, sun, sun_radius))
    return Eclipse::Lunar;
  else
    return Eclipse::None;
}

// Add a body
void
System::add_body (
	const Body body, const Vector3d r, const Vector3d v)
{
  bodies_.push_back(body);

  rs_.conservativeResize(NoChange, rs_.cols() + 1);
  rs_.rightCols<1>() = r;

  vs_.conservativeResize(NoChange, vs_.cols() + 1);
  vs_.rightCols<1>() = v;
}

// String formatter
string
System::str (void) const
{
  return str(false);
}

string
System::str (bool verbose) const
{
  ostringstream os;
  vector<Body>::size_type n = bodies_.size(), i;
  os << n << endl;

  for(i = 0; i != n; ++i)
    os << rs_.col(i).row(0) << " " << rs_.col(i).row(1) << " "
      << 1 /* bodies_[i].mass */ << endl;
  return os.str();
}

// Input/Output stream
std::istream&
operator>> (std::istream& is, System& s)
{
  string name;
  double rx, ry, rz, vx, vy, vz, m, R;

  is >> name >> rx >> ry >> rz >> vx >> vy >> vz >> m >> R;
  s.add_body(
      Body(m, R, name),
      Vector3d(rx, ry, rz), Vector3d(vx, vy, vz));
  return is;
}

std::ostream&
operator<< (std::ostream& os, const System& s)
{
  os << s.str();
  return os;
}
