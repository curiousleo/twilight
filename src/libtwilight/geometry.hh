// Twilight
//
// geometry.hh
// Geometry-related functions
//
// Provides functions to analyse the geometry of the constellation of
// sun, earth and moon.

#ifndef GUARD_geometry_hh
#define GUARD_geometry_hh

#include <cmath>

#include <Eigen/Dense>

/** Types of eclipses. */
enum class Eclipse
{
  None, Solar, Lunar
};

void
tangents (
    Eigen::Vector2d&, Eigen::Vector2d&,
    const Eigen::Vector2d&, const double, const Eigen::Vector2d&);

void
plane(
    Eigen::Vector2d&, Eigen::Vector2d&, Eigen::Vector2d&,
    const Eigen::Vector3d&, const Eigen::Vector3d&, const Eigen::Vector3d&);

bool
eclipse(
    const Eigen::Vector3d&, const double,
    const Eigen::Vector3d&, const double,
    const Eigen::Vector3d&, const double);

#endif // GUARD
