#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-09-08-ex5/parser.hpp>

struct OptimizationResult {
  double best_rate = 0.0;
  double best_v = 0.0;
  double best_q = 0.0;
  double best_cost = 0.0;
};

OptimizationResult OptimizeSupply(const Parameters& params, urng_t*rng);
