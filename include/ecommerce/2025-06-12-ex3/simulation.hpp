#pragma once

#include <vector>

#include <mocc/mocc.hpp>
#include <ecommerce/2025-06-12-ex3/parser.hpp>

struct OutputRecord {
  double time = 0.0;
  int value = 0;
};

std::vector<OutputRecord> SimulateCustomer(const Parameters& params, urng_t*rng);
