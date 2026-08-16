#pragma once

#include <mocc/mocc.hpp>

struct Stats {
  double avg = 0.0;
  double stddev = 0.0;
};

Stats SimulateCustomer(double avg, double stddev, int horizon, urng_t*rng);
