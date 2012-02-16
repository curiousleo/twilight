#include "geometry.hh"

using namespace std;
using namespace Eigen;

// Finds the two tangent lines from a circle (all in 2D). The first two
// arguments are references to vectors which will be set to the tangents
// found.
void
tangents (
    Vector2d& tangent1, Vector2d& tangent2,
    const Vector2d& centre, double radius, const Vector2d& point)
{
  Vector2d d = point - centre;
  Vector2d dnorm = d.normalized();
  // Norm vector at right angles to dnorm.
  Vector2d dir(-dnorm[1], dnorm[0]);
  double theta = asin(radius/d.norm());

  Vector2d tmp1 = centre + radius * sin(theta) * dnorm;
  Vector2d tmp2 = radius * cos(theta) * dir;

  tangent1 = tmp1 + tmp2;
  tangent2 = tmp1 - tmp2;

  return;
}

// Projects three points in 3D space onto the 2D plane defined by those
// three points. The projection of the first point becomes the origin of
// the projection plane.
void
plane(
    Vector2d& p1, Vector2d& p2, Vector2d& p3,
    const Vector3d& r1, const Vector3d& r2, const Vector3d& r3)
{
  Vector3d d12 = r2 - r1;
  Vector3d d13 = r3 - r1;
  Vector3d i = d12.normalized();
  Vector3d j = i.cross(d12.cross(d13)).normalized();

  // Origin of the plane (i, j) coordinate system.
  p1 = Vector2d(0, 0);
  // Component-wise projections via dot product.
  p2 = Vector2d(d12.dot(i), d12.dot(j));
  p3 = Vector2d(d13.dot(i), d13.dot(j));

  return;
}

// Check if we're having a solar eclipse
Eclipse
eclipse(
    const Vector2d& moon_centre,  const double moon_radius,
    const Vector2d& earth_centre, const double earth_radius,
    const Vector2d& sun_centre,   const double sun_radius)
{
  // Check if there is an eclipse at all. There is at least a partial
  // eclipse if 
  return Eclipse::None;
}

