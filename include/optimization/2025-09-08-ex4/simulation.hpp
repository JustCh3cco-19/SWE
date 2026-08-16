#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-09-08-ex4/parser.hpp>

struct OptimizationResult {
  double best_rate = 0.0;
  int best_suppliers = 0;
  double best_cost = 0.0;
};

OptimizationResult OptimizeSuppliers(const Parameters& params, urng_t*rng);
