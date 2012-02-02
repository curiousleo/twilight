#ifndef GUARD_numerics_hh
#define GUARD_numerics_hh

#include <functional>
#include <vector>

#include "vector3d.hh"

void euler(Vector3D&, Vector3D&, std::function<std::vector<Vector3D> >);
void rk4(Vector3D&, Vector3D&, std::function<std::vector<Vector3D> >);

#endif // GUARD
