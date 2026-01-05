#pragma once

#include "mocc.hpp"
#include "parser.hpp"

struct OptimizationResult {
  double best_p = 0.0;
  double best_rate = 0.0;
  double best_cost = 0.0;
};

OptimizationResult OptimizeP(const Parameters& params, urng_t* rng);
