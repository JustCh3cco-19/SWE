#include "parameters.h"
#include "ecommercesystem.h"
#include "customer.h"
#include "supplier.h"
#include "../mocc/exam_utils.hpp"
#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  Parameters params;
  if (!ReadParameters("parameters.txt", params)) {
    return 1;
  }

  double sum_rates = 0.0;

  for (int sim = 0; sim < params.M; ++sim) {
    urng_t rng = mocc_utils::MakeRng();
    System system;

    ECommerceSystem ecommercesystem(system, params, rng);

    // Crea customers
    std::vector<std::unique_ptr<Customer>> customers;
    customers.reserve(params.C);
    for (int i = 0; i < params.C; ++i) {
      customers.push_back(
          std::make_unique<Customer>(i, system, ecommercesystem, params, rng));
    }

    // Crea suppliers
    std::vector<std::unique_ptr<Supplier>> suppliers;
    suppliers.reserve(params.F);
    for (int i = 0; i < params.F; ++i) {
      suppliers.push_back(
          std::make_unique<Supplier>(i, system, ecommercesystem, params, rng));
    }

    // Simula per H secondi
    const int total_steps = static_cast<int>(std::ceil(params.H / params.T));
    for (int step = 0; step < total_steps; ++step) {
      system.next();
    }

    double rate = static_cast<double>(ecommercesystem.getMissedSales()) / params.H;
    sum_rates += rate;
  }

  const double expected_rate = sum_rates / params.M;

  bool success = mocc_utils::WriteResultsToFile(
      "results.txt",
      [&](std::ostream& out) {
        out << "R " << std::setprecision(10) << expected_rate << "\n";
      });

  if (!success) {
    std::cerr << "Cannot write results.txt\n";
    return 1;
  }

  return 0;
}
