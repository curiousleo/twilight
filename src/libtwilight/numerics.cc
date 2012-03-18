// Twilight
//
// numerics.cc
// Numerical integration functions

#include "numerics.hh"

using namespace std;
using namespace Eigen;

/**
 * The simplest integration method: Euler.
 * Global error and local error from E. Kreyszig: Advanced Engineering
 * Mathematics, 10th ed., p. 905, table 21.7.
 * 1 evaluation per step; global error O(dt); local error O(dt^2).
 */
void
euler (System* system)
{
  // a1: acceleration vectors of all the bodies of the system
  Array3Xd a1 = system->gravitate(system->rs());

  // Update position and velocity vectors
  system->update_rs(system->vs() * system->dt());
  system->update_vs(a1 * system->dt());

  return;
}

/**
 * Slightly more advanced than Euler: The Heun method, also known as
 * "Predictor-corrector" method.
 * 2 evaluations per step; global error O(dt^2); local error O(dt^3).
 */
void
heun (System* system)
{
  // r: positions
  // v: velocities
  // a: accelerations
  Array3Xd r1 = system->rs();
  Array3Xd v1 = system->vs();
  Array3Xd a1 = system->gravitate(r1);

  Array3Xd r2 = r1 + v1 * system->dt();
  Array3Xd v2 = v1 + a1 * system->dt();
  Array3Xd a2 = system->gravitate(r2);

  // Use arithmetic mean of predictor and corrector
  system->update_rs(0.5 * system->dt() * (v1 + v2));
  system->update_vs(0.5 * system->dt() * (a1 + a2));

  return;
}

/**
 * Gaussian quadrature.
 * 6 evaluations per step.
 */
void
gauss (System* system)
{
  // Points and weights taken from the table on the Wikipedia page on
  // Gaussian quadrature (with number of points n=5): http://ur1.ca/80erk
  Array3Xd r1 = system->rs();
  Array3Xd v1 = system->vs();
  Array3Xd a1 = system->gravitate(r1);

  // [ -(1/3) * sqrt(5 + 2 sqrt(10/7)) + 1 ] / 2
  Array3Xd r2 = r1 + v1 * 0.046910077030668 * system->dt();
  Array3Xd v2 = v1 + a1 * 0.046910077030668 * system->dt();
  Array3Xd a2 = system->gravitate(r1);

  // [ -(1/3) * sqrt(5 - 2 sqrt(10/7)) + 1 ] / 2
  Array3Xd r3 = r1 + v2 * 0.23076534494716 * system->dt();
  Array3Xd v3 = v1 + a2 * 0.23076534494716 * system->dt();
  Array3Xd a3 = system->gravitate(r2);

  // [ 0 + 1 ] / 2
  Array3Xd r4 = r1 + v3 * 0.5 * system->dt();
  Array3Xd v4 = v1 + a3 * 0.5 * system->dt();
  Array3Xd a4 = system->gravitate(r4);

  // [ (1/3) * sqrt(5 - 2 sqrt(10/7)) + 1 ] / 2
  Array3Xd r5 = r1 + v4 * 0.76923465505284 * system->dt();
  Array3Xd v5 = v1 + a4 * 0.76923465505284 * system->dt();
  Array3Xd a5 = system->gravitate(r5);

  // [ (1/3) * sqrt(5 + 2 sqrt(10/7)) + 1 ] / 2
  Array3Xd r6 = r1 + v5 * 0.95308992296933 * system->dt();
  Array3Xd v6 = v1 + a5 * 0.95308992296933 * system->dt();
  Array3Xd a6 = system->gravitate(r6);

  system->update_rs((
        // (322 - 13 * sqrt(70)) / 900
        0.23692688505619 * v2 +
        // (322 + 13 * sqrt(70)) / 900
        0.47862867049937 * v3 +
        // 128/225
        0.56888888888889 * v4 +
        // (322 + 13 * sqrt(70)) / 900
        0.47862867049937 * v5 +
        // (322 - 13 * sqrt(70)) / 900
        0.23692688505619 * v6
        ) * system->dt() / 2);
  system->update_vs((
        // (322 - 13 * sqrt(70)) / 900
        0.23692688505619 * a2 +
        // (322 + 13 * sqrt(70)) / 900
        0.47862867049937 * a3 +
        // 128/225
        0.56888888888889 * a4 +
        // (322 + 13 * sqrt(70)) / 900
        0.47862867049937 * a5 +
        // (322 - 13 * sqrt(70)) / 900
        0.23692688505619 * a6 
        ) * system->dt() / 2);

  return;
}

/**
 * Fourth-order Runge-Kutta (RK4).
 * 4 evaluations per step; global error O(dt^4); local error O(dt^5).
 */
void
rk4 (System* system)
{
  Array3Xd r1 = system->rs();
  Array3Xd v1 = system->vs();
  Array3Xd a1 = system->gravitate(r1);

  Array3Xd r2 = r1 + v1 * 0.5 * system->dt();
  Array3Xd v2 = v1 + a1 * 0.5 * system->dt();
  Array3Xd a2 = system->gravitate(r2);

  Array3Xd r3 = r1 + v2 * 0.5 * system->dt();
  Array3Xd v3 = v1 + a2 * 0.5 * system->dt();
  Array3Xd a3 = system->gravitate(r3);

  Array3Xd r4 = r1 + v3 * system->dt();
  Array3Xd v4 = v1 + a3 * system->dt();
  Array3Xd a4 = system->gravitate(r4);

  // Update this System with the weightened average values for r, v, a
  system->update_rs((system->dt()/6) * (v1 + 2 * (v2 + v3) + v4));
  system->update_vs((system->dt()/6) * (a1 + 2 * (a2 + a3) + a4));

  return;
}

/** Runge-Kutta-Fehlberg (RKF, a fifth-order Runge-Kutta method). */
void
rkf (System* system)
{
  Array3Xd r1 = system->rs();
  Array3Xd v1 = system->vs();
  Array3Xd a1 = system->gravitate(r1);

  // 1/4
  Array3Xd r2 = r1 + v1 * 0.25 * system->dt();
  Array3Xd v2 = v1 + a1 * 0.25 * system->dt();
  Array3Xd a2 = system->gravitate(r2);

  // 3/8
  Array3Xd r3 = r1 + v2 * 0.375 * system->dt();
  Array3Xd v3 = v1 + a2 * 0.375 * system->dt();
  Array3Xd a3 = system->gravitate(r3);

  // 12/13
  Array3Xd r4 = r1 + v3 * 0.92307692307692307692 * system->dt();
  Array3Xd v4 = v1 + a3 * 0.92307692307692307692 * system->dt();
  Array3Xd a4 = system->gravitate(r4);

  // 1
  Array3Xd r5 = r1 + v4 * system->dt();
  Array3Xd v5 = v1 + a4 * system->dt();
  Array3Xd a5 = system->gravitate(r5);

  // 1/2
  Array3Xd r6 = r1 + v5 * 0.5 * system->dt();
  Array3Xd v6 = v1 + a5 * 0.5 * system->dt();
  Array3Xd a6 = system->gravitate(r6);

  // Update this System with the weightened average values for r, v, a
  // Coefficients from E. Kreyszig: Advanced Engineering Mathematics,
  // 10th ed., p. 904
  system->update_rs((
              // 16/135
              0.11851851851851851852 * v1
        // +  0 * v2
              // 6656/12825
           +  0.51898635477582846004 * v3
              // 28561/56430
           +  0.50613149034201665781 * v4
              // -9/50
           -  0.18 * v5
              // 2/55
           +  0.03636363636363636364 * v6
          ) * system->dt());
  system->update_vs((
              // 16/135
              0.11851851851851851852 * a1
        // +  0 * a2
              // 6656/12825
           +  0.51898635477582846004 * a3
              // 28561/56430
           +  0.50613149034201665781 * a4
              // -9/50
           -  0.18 * a5
              // 2/55
           +  0.03636363636363636364 * a6
          ) * system->dt());

  return;
}
