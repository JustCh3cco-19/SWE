#include "parameters.h"
#include "network.h"
#include "customer.h"
#include "supplier.h"
#include "../mocc/exam_utils.hpp"
#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace {

double simulateWithV(const Parameters& base_params, double v_value) {
  Parameters params = base_params;
  params.V = v_value;
  params.W = v_value + 5.0;

  double sum_rates = 0.0;

  for (int sim = 0; sim < params.M; ++sim) {
    urng_t rng = mocc_utils::MakeRng();
    System system;

    Network network(system, params, rng);

    std::vector<std::unique_ptr<Customer>> customers;
    customers.reserve(params.C);
    for (int i = 0; i < params.C; ++i) {
      customers.push_back(
          std::make_unique<Customer>(i, system, network, params, rng));
    }

    std::vector<std::unique_ptr<Supplier>> suppliers;
    suppliers.reserve(params.F);
    for (int i = 0; i < params.F; ++i) {
      suppliers.push_back(
          std::make_unique<Supplier>(i, system, network, params, rng));
    }

    const int total_steps = static_cast<int>(params.H / params.T);
    for (int step = 0; step < total_steps; ++step) {
      system.next();
    }

    sum_rates += static_cast<double>(network.missedSales()) / params.H;
  }

  return sum_rates / params.M;
}

}

int main() {
  Parameters params;
  if (!ReadParameters("parameters.txt", params)) {
    return 1;
  }

  int best_v = 1;
  double best_r = 0.0;
  double best_j = std::numeric_limits<double>::infinity();

  int simulations_used = 0;
  int v_candidate = 1;

  while (simulations_used < params.G) {
    if (simulations_used + params.M > params.G) {
      break;
    }

    double r_value = simulateWithV(params, static_cast<double>(v_candidate));
    double j_value = params.a * v_candidate + params.b * r_value;

    simulations_used += params.M;

    if (j_value < best_j) {
      best_j = j_value;
      best_v = v_candidate;
      best_r = r_value;
      ++v_candidate;
    } else {
      break;
    }
  }

  if (!std::isfinite(best_j)) {
    double r_value = simulateWithV(params, 1.0);
    best_v = 1;
    best_r = r_value;
    best_j = params.a * best_v + params.b * r_value;
  }

  double best_w = best_v + 5.0;

  bool success = mocc_utils::WriteResultsToFile(
      "results.txt",
      [&](std::ostream& out) {
        out << "R " << std::setprecision(10) << best_r << "\n";
        out << "V " << std::setprecision(10) << static_cast<double>(best_v) << "\n";
        out << "W " << std::setprecision(10) << best_w << "\n";
        out << "J " << std::setprecision(10) << best_j << "\n";
      });

  if (!success) {
    std::cerr << "Cannot write results.txt\n";
    return 1;
  }

  return 0;
}
