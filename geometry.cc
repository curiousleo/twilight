#include "geometry.hh"

using namespace std;
using namespace Eigen;

void
tangencies (
    Vector2d& tangent1, Vector2d& tangent2,
    const Vector2d& centre, double radius, const Vector2d& point)
{
  Vector2d d = point - centre;
  Vector2d dnorm = d.normalized();
  Vector2d dir(-dnorm[1], dnorm[0]);
  double theta = asin(radius/d.norm());

  Vector2d tmp1 = centre + radius * sin(theta) * dnorm;
  Vector2d tmp2 = radius * cos(theta) * dir;

  tangent1 = tmp1 + tmp2;
  tangent2 = tmp1 - tmp2;

  return;
}

void
plane(
    Vector2d& p1, Vector2d& p2, Vector2d& p3,
    const Vector3d& r1, const Vector3d& r2, const Vector3d& r3)
{
  Vector3d d12 = r2 - r1;
  Vector3d d13 = r3 - r1;
  Vector3d i = d12.normalized();
  Vector3d j = i.cross(d12.cross(d13)).normalized();

  p1 = Vector2d(0, 0);
  p2 = Vector2d(d12.dot(i), d12.dot(j));
  p3 = Vector2d(d13.dot(i), d13.dot(j));

  return;
}
