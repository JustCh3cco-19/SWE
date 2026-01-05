#pragma once

#include "mocc.hpp"
#include "parser.hpp"

struct SimulationResult {
  int oversellings = 0;
  int transactions = 0;
};

SimulationResult RunSimulation(const Parameters& params, urng_t* rng);
double EstimateOversellings(const Parameters& params, int simulations, urng_t* rng);
