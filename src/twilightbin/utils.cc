#include <boost/program_options.hpp>

#include <libtwilight/libtwilight.hh>

using namespace std;
namespace po = boost::program_options;

int
cmdopts (
    int ac, char* av[],
    unsigned int& days, IntegrationMethod& method, double& dt)
{
  po::options_description desc("Options");
  desc.add_options()
    ("help,h", "print help message")
    (
      "days,n",
      po::value<unsigned int>(&days)->default_value(3650),
      "set duration of simulation (days)")
    (
      "dt,d",
      po::value<double>(&dt)->default_value(0.002, "0.002"),
      "set time step (days)")
    (
      "method,m",
      po::value<string>()->default_value("rkf"),
      "set integration method: 'euler', 'heun', 'gauss', 'rk4', or 'rkf'")
  ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cerr << desc << endl;
      exit(1);
    }

    if (vm.count("dt"))
      dt = vm["dt"].as<double>();

    if (vm.count("method")) {
      string mstr = vm["method"].as<string>();

      if (mstr == "euler")
        method = IntegrationMethod::Euler;
      else if (mstr == "heun")
        method = IntegrationMethod::Heun;
      else if (mstr == "gauss")
        method = IntegrationMethod::Gauss;
      else if (mstr == "rk4")
        method = IntegrationMethod::RK4;
      else if (mstr == "rkf")
        method = IntegrationMethod::RKF;
      else
        throw invalid_argument(
            "Unknown method :" + vm["method"].as<string>());
    }

    cerr << "Number of days: " << days
        << " | Time step: " << dt << " days"
        << " | Method: " << vm["method"].as<string>() << endl;
  }
  catch(exception& e)
  {
    cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}

