#pragma once

#include <vector>

#include "mocc.hpp"
#include "parser.hpp"

struct PositionRecord {
  double time = 0.0;
  int id = 0;
  double x = 0.0;
  double y = 0.0;
};

std::vector<PositionRecord> SimulatePositions(const Parameters& params, urng_t* rng);
