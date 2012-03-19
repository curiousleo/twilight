=========================
Predicting Solar Eclipses
=========================

Part IB Computing Optional Prize Problem
----------------------------------------

:Author:  Leonhard Markert
:Contact: lm510@cam.ac.uk
:Date:    Monday 19 March, 2012

Task
====

Numerically integrate the orbits of celestial bodies in order to predict
when solar eclipses will occur. Given are the positions, velocities,
masses, and radii of the Moon, Earth, and Sun at midnight on the
beginning of 7 January, 2008.

Program Design
==============

Usage
=====

``twilight -h`` shows the list of options and their defaults::

  Options:
  -h [ --help ]              print help message
  -n [ --days ] arg (=3650)  set duration of simulation (days)
  -d [ --dt ] arg (=0.002)   set time step (days)
  -m [ --method ] arg (=rkf) set integration method: 'euler',
                             'heun', 'gauss', 'rk4', or 'rkf'

Example: To run the simulation using the start data given on the
exercise web page (saved in ``system.in``) for twenty years (from 7
January, 2008) using the Gaussian quadrature method and a time step of
0.003 days, use ``twilight -n 7300 -d 0.003 -m gauss < system.in >
/dev/null``. This will discard the calculated positions (stdout) to
``/dev/null`` and print the dates at which solar eclipses occur to the
screen (via stderr).

Results
=======

Conclusions
===========

Libraries
=========

I made use of the following open source C++ libraries in my program:

Eigen (http://eigen.tuxfamily.org),
  a linear algebra library used by a number of scientific projects,
  amongst them the European Space Agency's Space Trajectory Analysis;

Boost.ProgramOptions (http://boost.org),
  a command line option parsing library.

Tools
=====

Whilst writing the code, I made use of the following open source tools:

Git
  (a distributed version control system) to manage the code;

Premake and GNU Make
  to simplify and speed up the compilation process;

GeoGebra
  to sketch diagrams of possible constellations of Sun, Earth and Moon
  as well as to find ways to construct tangents;

Python
  to analyse data and and write a script that downloads a list of dates
  of solar eclipses from Wikipedia;

show_sim
  (which I copied from the Department server) to visualise the movement
  of Sun, Earth and Moon, particularly in the early stages of the
  project.
