#pragma once

#include "mocc.hpp"
#include "parser.hpp"

struct OptimizationResult {
  double alpha = 0.0;
  double w_rate = 0.0;
  double s_rate = 0.0;
  double j_value = 0.0;
};

OptimizationResult OptimizeAlpha(const Parameters& params, int iterations, urng_t* rng);
