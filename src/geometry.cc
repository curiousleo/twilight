#include "geometry.hh"

using namespace std;
using namespace Eigen;

/**
 * Finds the two tangent lines from a point to a circle (all in 2D).
 *
 * \param tangent1 First tangent point on the circle
 * \param tangent2 Second tangent point on the circle
 * \param centre   Centre point of the circle
 * \param radius   Radius of the circle
 * \param point    Point from which to draw the tangents (must be
 *                 outside the circle)
 */
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

/**
 * Projects three points in 3D space onto the 2D plane defined by those
 * three points. The projection of the first point becomes the origin of
 * the projection plane.
 *
 * \param p1 Reference to the 2D projection of r1
 * \param p2 Reference to the 2D projection of r2
 * \param p3 Reference to the 2D projection of r3
 * \param r1 Point 1 (in 3D)
 * \param r2 Point 2 (in 3D)
 * \param r3 Point 3 (in 3D)
 */
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

/**
 * Check if body1 is casting a shadow on body2
 *
 * \param body1_centre Centre point of body 1
 * \param body1_radius Radius of body 1
 * \param body2_centre Centre point of body 2
 * \param body2_radius Radius of body 2
 * \param sun_centre   Centre point of the sun
 * \param sun_radius   Radius of the sun
 */
bool
eclipse(
    const Vector3d& body1_centre, const double body1_radius,
    const Vector3d& body2_centre, const double body2_radius,
    const Vector3d& sun_centre,   const double sun_radius)
{
  Vector2d homothetic;

  // Project everything onto a plane.
  Vector2d body1, body2, sun;
  plane(body1, body2, sun, body1_centre, body2_centre, sun_centre);

  // Check if there might be an eclipse.
  if ((body2 - sun).squaredNorm() < (body1 - sun).squaredNorm())
    return false;

  // Find external homothetic centre of sun and body2.
  homothetic =
      (body2 - sun) * body2_radius / (sun_radius - body2_radius);
  // Check if there is an eclipse at all: body2 must be nearer to
  // homothetic than body1.
  if ((body1 - homothetic).squaredNorm() <
      (body2 - homothetic).squaredNorm())
    return false;
  
  // Find tangent points from homothetic centre of sun and body2 to
  // body2 and body1 (sun and body2 are coincident as seen from the
  // homothetic centre, so we need only one of the two.)
  Vector2d body2_tangent1, body2_tangent2,
           body1_tangent1, body1_tangent2;
  tangents(body2_tangent1, body2_tangent2, body2, body2_radius, homothetic);
  tangents(body1_tangent1, body1_tangent2, body1, body1_radius, homothetic);

  // There is at least a partial eclipse if body1 is partly or fully
  // within the external sun-body2 bitangent lines.
  Vector2d r = (body2 - sun).normalized();
  double cosphi    = fabs(r.dot((body2_tangent1 - homothetic).normalized()));
  double costheta1 = fabs(r.dot((body1_tangent1 - homothetic).normalized()));
  double costheta2 = fabs(r.dot((body1_tangent2 - homothetic).normalized()));

  if (costheta1 < cosphi || costheta2 < cosphi)
    return true;
  else
    return false;
}

