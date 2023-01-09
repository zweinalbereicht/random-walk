#include <cmath>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../walkers/GaussianWalker.h"

#include "Observables.h"

#define LOG(x) cout << x << endl;
#define MOD(x) fmod(x + (2.0 * M_PI), (2.0 * M_PI))

// this is a constant to make sure our program terminates because we have
// infinite mean return time. 1 billion might actually be big.
#define MAX_SIMU_STEPS 1000000000

using namespace std;
namespace py = pybind11;

void print_vec(std::vector<double> vec) {
  for (auto el : vec) {
    std::cout << el << std::endl;
  }
}

double split_prob_hyperplane(const double x0, const double x,
                             GaussianWalker &walker, const int n) {
  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, x0);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    while (walker.get_pos()[0] >= 0 && walker.get_pos()[0] <= x) {
      walker.move();
    }
    run += (walker.get_pos()[0] > 0);
  }
  return (run / ((double)n));
}

// the walker starts on the x axis, at distance x0 from the origin
double split_prob_cone(const double r0, const double theta0, const double theta,
                       GaussianWalker &walker, const int n) {
  vector<int> result_tmp(n);
  vector<double> last_pos;
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, r0 * cos(theta0));
    walker.set_coord(1, r0 * sin(theta0));
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    double angle = walker.get_angle();
    while (angle >= 0 && angle <= theta) {
      last_pos = walker.get_pos();
      walker.move();
      // this should copy alright
      angle = walker.get_angle();
    }
    // This is not exact, there are some cases where we are not able to say
    // which side the cone was exited from, but it should be decent enough

    // we now modify this to make it more exact (still not perfect I think,
    // works for a cone smaller than pi/2 at least.)
    if (-M_PI_2 <= angle && angle <= 0) {
      run += 0;
    } else if (theta <= angle && angle <= M_PI) {
      run += 1;
    } else { // this is the case where either crossing could happen
      // this will only work in 2D, as we use scalar products
      // print_vec(last_pos);
      // print_vec(walker.get_pos());
      // std::cout << last_pos[0] << "," << walker.get_pos()[0] << std::endl;
      vector<double> curr_pos = walker.get_pos();
      double scalar_product = -last_pos[1] * (curr_pos[0] - last_pos[0]) +
                              last_pos[0] * (curr_pos[1] - last_pos[1]);
      int score = (int)(scalar_product > 0);
      run += score;
    }
  }
  return (run / ((double)n));
}

// the walker starts on the x axis, at distance x0 from the origin
double split_prob_reflecting_cone(const double r0, const double theta0,
                                  const double theta, const double R,
                                  GaussianWalker &walker, const int n) {
  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, r0 * cos(theta0));
    walker.set_coord(1, r0 * sin(theta0));
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    std::vector<double> last_pos = walker.get_pos();
    double angle = walker.get_angle();
    while (angle >= 0 && angle <= theta) {
      last_pos = walker.get_pos();
      walker.move();
      // if we step outside the cone we cancel the move
      if (walker.get_radial_dist() > R) {
        int dimension = walker.get_dimension();
        for (int i = 0.; i < dimension; i++) {
          walker.set_coord(i, last_pos[i]);
        }
      }
      angle = walker.get_angle();
    }

    if (-M_PI_2 <= angle && angle <= 0) {
      run += 0;
    } else if (theta <= angle && angle <= M_PI) {
      run += 1;
    } else { // this is the case where either crossing could happen
      vector<double> curr_pos = walker.get_pos();
      double scalar_product = -last_pos[1] * (curr_pos[0] - last_pos[0]) +
                              last_pos[0] * (curr_pos[1] - last_pos[1]);
      int score = (int)(scalar_product > 0);
      run += score;
    }
  }
  return (run / ((double)n));
}

double split_prob_disk_escape(const double R, const double theta1,
                              const double theta2, GaussianWalker &walker,
                              const int n) {

  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, -R);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    std::vector<double> last_pos = walker.get_pos();
    while (walker.get_radial_dist() <= R) {
      walker.move();
    }
    // Once we step outside we look at our angle (in the 0,2pi range)
    double angle = MOD(walker.get_angle());
    run += (int)(angle > theta1 && angle < theta2);
  }
  return (run / ((double)n));
}

double split_prob_concentric_disk(const double R_int, const double R_out,
                                  GaussianWalker &walker, const int n) {

  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, R_int);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    std::vector<double> last_pos = walker.get_pos();
    while (walker.get_radial_dist() >= R_int &&
           walker.get_radial_dist() <= R_out) {
      walker.move();
    }

    run += (int)(walker.get_radial_dist() >= R_out);
  }
  return (run / ((double)n));
}

// returns the probability to escape eccentric discs via the farthest one. We
// start on the smallest radius whose center is offsetted and with an angle
// theta0 wrt to the center of the inner circle
//
// Note that this work mostly in 2D, 3D would need some updates (we have one
// more angular component.)
double split_prob_eccentric_disk(const double R_int, const double R_out,
                                 double const offset, double const theta0,
                                 GaussianWalker &walker, const int n) {

  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, -offset + R_int * cos(theta0));
    walker.set_coord(1, R_int * sin(theta0));

    // initialize vector center --> only works in 3D
    vector<double> inner_centre(2);
    inner_centre[0] = -offset;
    inner_centre[1] = 0.0;
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++) {
      walker.set_coord(k, 0.0);
    }

    // run
    std::vector<double> last_pos = walker.get_pos();
    // cout << euclidian_distance(walker.get_pos(), inner_centre) << endl;
    while (euclidian_distance(walker.get_pos(), inner_centre) >= R_int &&
           walker.get_radial_dist() <= R_out) {
      // cout << euclidian_distance(walker.get_pos(), inner_centre) << endl;
      walker.move();
    }

    run += (int)(walker.get_radial_dist() >= R_out);
  }
  return (run / ((double)n));
}

// returns the probability to escape eccentric discs via the farthest one. We
// start on the smallest radius whose center is offsetted and with an angle
// theta0 wrt to the center of the inner circle
py::list fpt_distribution_eccentric_inner_disk_outer_reflecting(
    const double R_int, const double R_out, double const offset,
    double const theta0, GaussianWalker &walker, const int n) {

  vector<int> result_tmp(n);
  for (int i = 0; i < n; i++) {

    // prepare for the run

    walker.set_lifetime(0);
    walker.set_coord(0, -offset + R_int * cos(theta0));
    walker.set_coord(1, R_int * sin(theta0));

    // initialize vector center --> only works in 2D
    vector<double> inner_centre(2);
    inner_centre[0] = -offset;
    inner_centre[1] = 0.0;
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++) {
      walker.set_coord(k, 0.0);
    }

    double counter = 0;

    // run
    // cout << euclidian_distance(walker.get_pos(), inner_centre) << endl;
    while (euclidian_distance(walker.get_pos(), inner_centre) >= R_int) {
      counter += 1;
      walker.move();
      double r = walker.get_radial_dist();
      if (r > R_out) {
        walker.set_coord(0, (2 * R_out - r) / r * walker.get_pos()[0]);
        walker.set_coord(1, (2 * R_out - r) / r * walker.get_pos()[1]);
      }
    }
    result_tmp[i] = counter;
  }
  // casting at the end
  py::list ret = py::cast(result_tmp);
  return ret;
}

// same as above but we start anywhere in the disk
py::list fpt_distribution_eccentric_inner_disk_outer_reflecting_any_position(
    const double R_int, const double R_out, double const offset,
    double const r0, double const theta0, GaussianWalker &walker, const int n) {

  vector<int> result_tmp(n);
  for (int i = 0; i < n; i++) {

    // prepare for the run

    walker.set_lifetime(0);
    walker.set_coord(0, r0 * cos(theta0));
    walker.set_coord(1, r0 * sin(theta0));

    // initialize vector center --> only works in 2D
    vector<double> inner_centre(2);
    inner_centre[0] = -offset;
    inner_centre[1] = 0.0;
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++) {
      walker.set_coord(k, 0.0);
    }

    double counter = 0;

    // run
    // cout << euclidian_distance(walker.get_pos(), inner_centre) << endl;
    while (euclidian_distance(walker.get_pos(), inner_centre) >= R_int) {
      counter += 1;
      walker.move();
      double r = walker.get_radial_dist();
      if (r > R_out) {
        walker.set_coord(0, (2 * R_out - r) / r * walker.get_pos()[0]);
        walker.set_coord(1, (2 * R_out - r) / r * walker.get_pos()[1]);
      }
    }
    result_tmp[i] = counter;
  }
  // casting at the end
  py::list ret = py::cast(result_tmp);
  return ret;
}

// returns the mean fpt to inner disk with outer disk reflecting
double mfpt_2d_disk_outer_reflecting(const double R_int, const double R_out,
                                     GaussianWalker &walker, const int n) {

  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    double counter = 0;
    walker.set_lifetime(0);
    walker.set_coord(0, R_int);
    vector<double> inner_centre(2);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++) {
      walker.set_coord(k, 0.0);
    }

    // run
    std::vector<double> last_pos = walker.get_pos();
    // cout << euclidian_distance(walker.get_pos(), inner_centre) << endl;
    while (walker.get_radial_dist() >= R_int) {
      counter += 1;
      walker.move();
      double r = walker.get_radial_dist();
      if (r > R_out) {
        walker.set_coord(0, (2 * R_out - r) / r * walker.get_pos()[0]);
        walker.set_coord(1, (2 * R_out - r) / r * walker.get_pos()[1]);
      }
      std::vector<double> last_pos = walker.get_pos();
    }
    run += counter;
  }
  return (run / ((double)n));
}

// returns the probability to survive n steps in a disk of radiius R
double survival_disk(const double R, const int nbsteps, GaussianWalker &walker,
                     const int n) {
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    int counter = 0;
    walker.set_lifetime(0);
    walker.set_coord(0, -R);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    while ((walker.get_radial_dist() <= R) && (counter < nbsteps)) {
      walker.move();
      counter++;
    }
    double rad = walker.get_radial_dist();
    run += (double)(rad <= R);
  }
  return (run / ((double)n));
}

py::list radial_distance_when_crossing_hyperplan_distribution(
    const double x0, const double x, GaussianWalker &walker, const int n) {
  vector<float> distances(n);
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, x0);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run until we cross 0. Watch out as this can never terminate, we need to
    // input manually an upper bound on the number of steps to make sure out
    // program doesn't run for too long.
    while (walker.get_pos()[0] >= 0 && walker.get_lifetime() < MAX_SIMU_STEPS) {
      walker.move();
    }
    //
    // calculate the distance by projecting and then computing the
    // euclidian distance to 0, which is the projected distance of the
    // starting point.
    if (walker.get_lifetime() == MAX_SIMU_STEPS) {
      distances[i] = 0; // set to zero, shoudn't have much impact.
    } else {
      walker.set_coord(0, 0);
      distances[i] = euclidian_distance(walker.get_pos());
    }
  }
  py::list ret = py::cast(distances);
  return ret;
}
