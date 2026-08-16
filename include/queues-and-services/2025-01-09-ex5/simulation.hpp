#pragma once

#include <vector>

#include <mocc/mocc.hpp>

struct DispatcherResult {
  std::vector<long long> counts;
  bool violation = false;
};

DispatcherResult SimulateDispatcher(
  int num_customers,
  double avg,
  double stddev,
  int horizon,
  urng_t*rng
  );
