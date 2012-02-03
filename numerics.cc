#include "numerics.hh"

using namespace std;
using namespace Eigen;

void euler(System* system) {
    // rs and vs are the initial positions and velocities, respectively
    // a is a function that takes the list of positions and returns a
    // list of accelerations
    Array3Xd as_tmp = system->gravitate(system->rs);

    system->rs += system->vs * system->dt;
    system->vs += as_tmp * system->dt;

    return;
}

void rk4(System* system) {
    // rs and vs are the initial positions and velocities, respectively
    // a is a function that takes the list of positions and returns a
    // list of accelerations

    /*
    x1 = x
    v1 = v
    a1 = a(x1, v1, 0)

    x2 = x + 0.5*v1*dt
    v2 = v + 0.5*a1*dt
    a2 = a(x2, v2, dt/2.0)

    x3 = x + 0.5*v2*dt
    v3 = v + 0.5*a2*dt
    a3 = a(x3, v3, dt/2.0)

    x4 = x + v3*dt
    v4 = v + a3*dt
    a4 = a(x4, v4, dt)

    xf = x + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4)
    vf = v + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4)
    */
    Array3Xd r1 = system->rs;
    Array3Xd v1 = system->vs;
    Array3Xd a1 = system->gravitate(r1);

    Array3Xd r2 = r1 + v1 * 0.5 * system->dt;
    Array3Xd v2 = v1 + a1 * 0.5 * system->dt;
    Array3Xd a2 = system->gravitate(r2);

    Array3Xd r3 = r1 + v2 * 0.5 * system->dt;
    Array3Xd v3 = v1 + a2 * 0.5 * system->dt;
    Array3Xd a3 = system->gravitate(r3);

    Array3Xd r4 = r1 + v3 * system->dt;
    Array3Xd v4 = v1 + a3 * system->dt;
    Array3Xd a4 = system->gravitate(r4);

    // Update this System with the weightened average values for r, v, a
    system->rs += (system->dt/6) * (v1 + 2 * (v2 + v3) + v4);
    system->vs += (system->dt/6) * (a1 + 2 * (a2 + a3) + a4);

    return;
}
