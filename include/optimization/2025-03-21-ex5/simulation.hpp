#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-03-21-ex5/parser.hpp>

struct OptimizationResult {
  double alpha = 0.0;
  double w_rate = 0.0;
  double s_rate = 0.0;
  double j_value = 0.0;
};

OptimizationResult OptimizeAlpha(const Parameters& params, int iterations, urng_t*rng);
