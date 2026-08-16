#pragma once

#include <mocc/mocc.hpp>
#include <optimization/2025-03-21-ex2/parser.hpp>

struct OptimizationResult {
  double best_alpha = 0.0;
  double best_fraction = 0.0;
};

OptimizationResult OptimizeAlpha(const Parameters& params, int iterations, urng_t*rng);
