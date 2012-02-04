#include <boost/program_options.hpp>

#include "physics.hh"
#include "date.hh"

using namespace std;
namespace po = boost::program_options;

int cmdopts(int ac, char* av[], unsigned int& days, IntegrationMethod& method, double& dt) {
    po::options_description desc("Allowed options");
    desc.add_options()
	// ("help", "produce help message")
	("days,n", po::value<unsigned int>(&days)->default_value(2400), "time step (in days)")
	("dt,d", po::value<double>(&dt)->default_value(0.005), "time step (in days)")
	("method,m", po::value<string>()->default_value("rkf"), "integration method")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    /*
    if (vm.count("help")) {
	cerr << desc << "\n";
	return 1;
    }
    */

    if (vm.count("dt"))
	dt = vm["dt"].as<double>();

    if (vm.count("method")) {
	string mstr = vm["method"].as<string>();

	if (mstr == "euler")     method = IntegrationMethod::Euler;
	else if (mstr == "heun") method = IntegrationMethod::Heun;
	else if (mstr == "rk4")  method = IntegrationMethod::RK4;
	else if (mstr == "rkf")  method = IntegrationMethod::RKF;
    }

    cerr << "Number of days: " << days
	    << " | Time step: " << dt << " days"
	    << " | Method: " << vm["method"].as<string>() << endl;

    return 0;
}

int main(int ac, char* av[]) {
    unsigned int i, interval, planets, days;
    double t, dt;
    IntegrationMethod method;
    Eclipse eclipse;

    Date start(2008, 1, 7);
    int lasteclipse = -1;

    cmdopts(ac, av, days, method, dt);

    interval = floor(days / (dt * 200.0));

    System system(method, dt);

    cin >> planets;
    for (i = 0; i != planets; i++) cin >> system;
    i = 0;

    for (t = 0; t < (double)days; t += dt) {
	eclipse = system.pulse();

        if (eclipse != Eclipse::None && floor(t) != lasteclipse) {
            lasteclipse = floor(t);

            cerr << start + lasteclipse << ",";

	    if (eclipse == Eclipse::Lunar) cerr << "Lunar" << endl;
	    else cerr << "Solar" << endl;
        }
        if (++i == interval) {
            cout << system;
            i = 0;
        }
    }
    cerr << endl;

    return 0;
}
