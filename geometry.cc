#include "geometry.hh"

using namespace std;
using namespace Eigen;

// Finds the two tangent lines from a circle (all in 2D). The first two
// arguments are references to vectors which will be set to the tangents
// found.
void
tangents (
    Vector2d& tangent1, Vector2d& tangent2,
    const Vector2d& centre, const double radius, const Vector2d& point)
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
    const Vector3d& moon_centre,  const double moon_radius,
    const Vector3d& earth_centre, const double earth_radius,
    const Vector3d& sun_centre,   const double sun_radius)
{
  // Project everything onto a plane.
  Vector2d moon, earth, sun;
  plane(moon, earth, sun, moon_centre, earth_centre, sun_centre);

  // Check if there is a solar eclipse at all.
  if ((earth - sun).squaredNorm() < (moon - sun).squaredNorm())
    return Eclipse::None;

  // Find external homothetic centre of sun and earth.
  Vector2d homothetic =
      (earth - sun) * earth_radius / (sun_radius - earth_radius);
  
  // Again, check if there is an eclipse at all: Earth must be nearer to
  // homothetic than moon.
  if ((moon - homothetic).squaredNorm() < (earth - homothetic).squaredNorm())
    return Eclipse::None;

  // Find tangent points from homothetic centre of sun and earth to
  // earth and moon (sun and earth are coincident as seen from the
  // homothetic centre, so we need only one of the two.)
  Vector2d earth_tangent1, earth_tangent2,
           moon_tangent1, moon_tangent2;
  tangents(earth_tangent1, earth_tangent2, earth, earth_radius, homothetic);
  tangents(moon_tangent1, moon_tangent2, moon, moon_radius, homothetic);

  // There is at least a partial eclipse if the moon is partly or fully
  // within the external sun-earth bitangent lines.
  Vector2d r = (earth - sun).normalized();
  double cosphi    = fabs(r.dot((earth_tangent1 - homothetic).normalized()));
  double costheta1 = fabs(r.dot((moon_tangent1 - homothetic).normalized()));
  double costheta2 = fabs(r.dot((moon_tangent2 - homothetic).normalized()));

  if (costheta1 < cosphi || costheta2 < cosphi)
    return Eclipse::PartialSolar;


  return Eclipse::None;
}

