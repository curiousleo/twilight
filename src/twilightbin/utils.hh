// Twilight
//
// utils.hh
// Utility functions used by the main function
//
// cmdopts, write_dates, write_positions

#ifndef GUARD_utils_hh
#define GUARD_utils_hh

int
cmdopts (
    int ac, char* av[],
    unsigned int& days, IntegrationMethod& method, double& dt);

#endif // GUARD
