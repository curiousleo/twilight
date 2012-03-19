~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Part IB Computing Optional Prize Problem
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:Author:  Leonhard Markert
:Contact: lm510@cam.ac.uk
:Date:    Monday 19 March, 2012

Task
~~~~

Numerically integrate the orbits of celestial bodies in order to predict
when solar eclipses will occur. Given are the positions, velocities,
masses, and radii of the Moon, Earth, and Sun at midnight on the
beginning of 7 January, 2008.

Libraries
~~~~~~~~~

I use the following open source C++ libraries in my program:

Eigen (http://eigen.tuxfamily.org)
  a linear algebra library used by a number of scientific projects,
  amongst them the European Space Agency's Space Trajectory Analysis;

Boost.ProgramOptions (http://boost.org)
  a command line option parsing library.

Tools
~~~~~

Whilst writing the code, I made use of the following tools:

Git
  (a distributed version control system) to manage the code;

Premake
  to automatically create GNU Makefiles;

GNU Make
  to simplify and speed up the compilation;

Doxygen
  the source code documentation tool;

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
