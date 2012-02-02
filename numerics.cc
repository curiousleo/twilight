#include "numerics.hh"

using namespace std;

void euler(System* system) {
    // rs and vs are the initial positions and velocities, respectively
    // a is a function that takes the list of positions and returns a
    // list of accelerations
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

    const vector<Vector3D>::size_type n = system->rs.size();
    vector<Vector3D>::size_type j;

    vector<Vector3D> r1(system->rs), v1(system->vs), a1 = system->gravitate(r1),
                     r2, v2, a2,
                     r3, v3, a3,
                     r4, v4, a4;

    for (j = 0; j != n; j++) {
        r2.push_back(r1[j] + v1[j] * 0.5 * system->dt);
        v2.push_back(v1[j] + a1[j] * 0.5 * system->dt);
    }

    a2 = system->gravitate(r2);

    for (j = 0; j != n; j++) {
        r3.push_back(r1[j] + v2[j] * 0.5 * system->dt);
        v3.push_back(v1[j] + a2[j] * 0.5 * system->dt);
    }

    a3 = system->gravitate(r3);
    for (j = 0; j != n; j++) {
        r4.push_back(r1[j] + v3[j] * system->dt);
        v4.push_back(v1[j] + a3[j] * system->dt);
    }

    a4 = system->gravitate(r4);

    // Update this System with the weightened average values for r, v, a
    for (j = 0; j != n; j++) {
        system->rs[j] += (system->dt/6) * (v1[j] + 2 * (v2[j] + v3[j]) + v4[j]);
        system->vs[j] += (system->dt/6) * (a1[j] + 2 * (a2[j] + a3[j]) + a4[j]);
    }

    return;
}
