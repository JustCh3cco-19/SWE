#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-06-12-ex5/parser.hpp>

struct OptimizationResult {
  double best_p = 0.0;
  double best_q = 0.0;
};

OptimizationResult OptimizeP(const Parameters& params, urng_t*rng);
