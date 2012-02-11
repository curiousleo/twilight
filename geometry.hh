#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <cmath>

#include <algorithm>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Geometry>

void
tangencies (
    Eigen::Vector2d&, Eigen::Vector2d&,
    const Eigen::Vector2d&, double, const Eigen::Vector2d&);

void
plane(
    Eigen::Vector2d&, Eigen::Vector2d&, Eigen::Vector2d&,
    const Eigen::Vector3d&, const Eigen::Vector3d&, const Eigen::Vector3d&);

#endif // GUARD
