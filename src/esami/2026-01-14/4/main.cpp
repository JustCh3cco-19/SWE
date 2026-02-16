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
#include <limits>
#include <memory>
#include <vector>

// Simula con F fornitori e ritorna il rate di mancate vendite
double simulateWithSuppliers(const Parameters& params, int F) {
  double sum_rates = 0.0;

  for (int sim = 0; sim < params.M; ++sim) {
    urng_t rng = mocc_utils::MakeRng();
    System system;

    ECommerceSystem ecommerce(system, params, rng);

    // Crea customers
    std::vector<std::unique_ptr<Customer>> customers;
    customers.reserve(params.C);
    for (int i = 0; i < params.C; ++i) {
      customers.push_back(
          std::make_unique<Customer>(i, system, ecommerce, params, rng));
    }

    // Crea F suppliers
    std::vector<std::unique_ptr<Supplier>> suppliers;
    suppliers.reserve(F);
    for (int i = 0; i < F; ++i) {
      suppliers.push_back(
          std::make_unique<Supplier>(i, system, ecommerce, params, rng));
    }

    // Simula per H secondi
    const int total_steps = static_cast<int>(std::ceil(params.H / params.T));
    for (int step = 0; step < total_steps; ++step) {
      system.next();
    }

    sum_rates += static_cast<double>(ecommerce.getMissedSales()) / params.H;
  }

  return sum_rates / params.M;
}

int main() {
  Parameters params;
  if (!ReadParameters("parameters.txt", params)) {
    return 1;
  }

  // Ottimizzazione: cerca il miglior F entro il budget G
  int best_F = 1;
  double best_R = 0.0;
  double best_J = std::numeric_limits<double>::infinity();

  int simulations_used = 0;
  int F_candidate = 1;

  // Strategia: prova valori crescenti di F finché il costo aumenta o finisce il budget
  while (simulations_used < params.G) {
    // Ogni valutazione costa M simulazioni
    if (simulations_used + params.M > params.G) {
      break;  // Non abbastanza budget rimasto
    }

    double R = simulateWithSuppliers(params, F_candidate);
    double J = params.a * F_candidate + params.b * R;

    simulations_used += params.M;

    if (J < best_J) {
      best_J = J;
      best_F = F_candidate;
      best_R = R;
      F_candidate++;  // Prova il prossimo
    } else {
      // Il costo è aumentato, trovato il minimo locale
      break;
    }
  }

  bool success = mocc_utils::WriteResultsToFile(
      "results.txt",
      [&](std::ostream& out) {
        out << "R " << std::setprecision(10) << best_R << "\n";
        out << "F " << best_F << "\n";
        out << "J " << std::setprecision(10) << best_J << "\n";
      });

  if (!success) {
    std::cerr << "Cannot write results.txt\n";
    return 1;
  }

  return 0;
}
