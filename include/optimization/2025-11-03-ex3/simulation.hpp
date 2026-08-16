#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-11-03-ex3/parser.hpp>

struct OptimizationResult {
  double best_p = 0.0;
  double best_cost = 0.0;
  double best_total = 0.0;
};

OptimizationResult OptimizeP(const Parameters& params, urng_t*rng);
