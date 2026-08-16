#pragma once

#include <mocc/mocc.hpp>
#include <ecommerce/2025-03-21-ex3/parser.hpp>

struct SimulationResult {
  int oversellings = 0;
  int transactions = 0;
};

SimulationResult RunSimulation(const Parameters& params, urng_t*rng);
double EstimateOversellings(const Parameters& params, int simulations, urng_t*rng);
