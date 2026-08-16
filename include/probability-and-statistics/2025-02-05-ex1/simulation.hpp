#pragma once

#include <vector>

#include <mocc/mocc.hpp>
#include <probability-and-statistics/2025-02-05-ex1/parser.hpp>

std::vector<double> SimulateCoverage(
  const Parameters& params,
  urng_t*rng
  );
