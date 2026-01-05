#pragma once

#include <vector>

#include "mocc.hpp"
#include "parser.hpp"

struct OutputRecord {
  double time = 0.0;
  int value = 0;
};

std::vector<OutputRecord> SimulateCustomer(const Parameters& params, urng_t* rng);
