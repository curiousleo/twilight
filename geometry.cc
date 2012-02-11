#include "geometry.hh"

using namespace std;
using namespace Eigen;

pair<Vector2d, Vector2d>
tangencies (
    const Vector2d& centre, double radius, const Vector2d& point)
{
  Vector2d d = point - centre;
  Vector2d dnorm = d.normalized();
  double norm = d.norm();
  double theta = asin(radius/norm);

  Vector2d tmp1 = centre + radius * sin(theta) * dnorm;
  Vector2d dir(-dnorm[1], dnorm[0]);
  Vector2d tmp2 = radius * cos(theta) * dir;

  return pair<Vector2d, Vector2d>(tmp1 + tmp2, tmp1 - tmp2);
}

Hyperplane<double, 3>
plane(const Array3Xd& rs)
{
  return Hyperplane<double, 3>::Through(rs.col(0), rs.col(1), rs.col(2));
}
