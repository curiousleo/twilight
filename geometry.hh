#ifndef GUARD_physics_hh
#define GUARD_physics_hh

#include <cmath>

#include <Eigen/Dense>

std::pair<Eigen::Vector2d, Eigen::Vector2d>
tangencies (const Eigen::Vector2d&, double, const Eigen::Vector2d&);

Eigen::Array2Xd
plane(Eigen::Array3Xd&);

#endif // GUARD
