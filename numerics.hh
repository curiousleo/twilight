#ifndef GUARD_numerics_hh
#define GUARD_numerics_hh

#include <functional>
#include <vector>

#include "vector3d.hh"

void euler(
	std::vector<Vector3D>&, std::vector<Vector3D>&, const double,
	std::function<std::vector<Vector3D>()>);
void rk4(
	std::vector<Vector3D>&, std::vector<Vector3D>&, const double,
	std::function<std::vector<Vector3D>()>);

#endif // GUARD
