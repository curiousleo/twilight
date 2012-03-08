// Twilight
//
// numerics.hh
// Numerical integration functions
//
// Provides different numerical integration methods.

#ifndef GUARD_numerics_hh
#define GUARD_numerics_hh

#include "physics.hh"

void euler (System*);
void heun (System*);
void gauss (System*);
void rk4 (System*);
void rkf (System*);

#endif // GUARD
