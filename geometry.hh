#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <cmath>

#include <Eigen/Dense>
#include <Eigen/Geometry>

std::pair<Eigen::Vector2d, Eigen::Vector2d>
tangencies (const Eigen::Vector2d&, double, const Eigen::Vector2d&);

Eigen::Hyperplane<double, 3>
plane(const Eigen::Array3Xd&);

#endif // GUARD
