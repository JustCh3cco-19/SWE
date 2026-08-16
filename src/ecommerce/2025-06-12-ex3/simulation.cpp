#include <ecommerce/2025-06-12-ex3/simulation.hpp>

#include <random>
#include <vector>

std::vector<OutputRecord> SimulateCustomer(const Parameters& params, urng_t*rng) {
  std::vector<OutputRecord> records;
  if (!rng || params.time_step <= 0.0) {
    return records;
  }

  std::uniform_real_distribution<double> wait_dist(params.min_wait, params.max_wait);
  std::uniform_int_distribution<int> product_dist(1, params.num_products);

  int steps = static_cast<int>(params.horizon / params.time_step);
  double remaining = 0.0;
  int current_product = product_dist(*rng);
  remaining = wait_dist(*rng);

  for (int step = 0; step <= steps; ++step) {
    double time = step * params.time_step;
    if (step == 0) {
      records.push_back(OutputRecord{time, current_product});
      continue;
    }

    remaining -= params.time_step;
    if (remaining <= 0.0) {
      current_product = product_dist(*rng);
      remaining = wait_dist(*rng);
      records.push_back(OutputRecord{time, current_product});
    } else {
      records.push_back(OutputRecord{time, 0});
    }
  }

  return records;
}
