#include "simulation.hpp"

#include <queue>
#include <random>
#include <vector>

namespace {

double RunSimulation(const Parameters& params, urng_t* rng) {
  std::uniform_real_distribution<double> customer_wait(params.min_wait, params.max_wait);
  std::uniform_real_distribution<double> server_wait(params.min_server, params.max_server);
  std::uniform_real_distribution<double> unit(0.0, 1.0);
  std::uniform_int_distribution<int> product_dist(1, params.num_products);
  std::uniform_int_distribution<int> stock_dist(0, params.max_items);

  std::queue<int> requests;
  std::vector<int> stock(static_cast<std::size_t>(params.num_products), 0);
  for (int p = 0; p < params.num_products; ++p) {
    stock[static_cast<std::size_t>(p)] = stock_dist(*rng);
  }

  double customer_timer = customer_wait(*rng);
  double server_timer = server_wait(*rng);

  int steps = static_cast<int>(params.horizon / params.time_step);
  long long missed = 0;

  for (int step = 0; step < steps; ++step) {
    customer_timer -= params.time_step;
    if (customer_timer <= 0.0) {
      requests.push(product_dist(*rng));
      customer_timer = customer_wait(*rng);
    }

    server_timer -= params.time_step;
    if (server_timer <= 0.0) {
      if (!requests.empty()) {
        int product = requests.front();
        requests.pop();
        std::size_t idx = static_cast<std::size_t>(product - 1);
        if (stock[idx] > 0) {
          stock[idx] -= 1;
        } else {
          missed += 1;
          if (unit(*rng) <= params.prob) {
            stock[idx] = stock_dist(*rng);
          }
        }
      }
      server_timer = server_wait(*rng);
    }
  }

  double total_time = steps * params.time_step;
  if (total_time <= 0.0) {
    return 0.0;
  }
  return missed / total_time;
}

}  // namespace

double EstimateMissRate(const Parameters& params, urng_t* rng) {
  if (!rng || params.simulations <= 0) {
    return 0.0;
  }

  double total = 0.0;
  for (int i = 0; i < params.simulations; ++i) {
    total += RunSimulation(params, rng);
  }
  return total / params.simulations;
}
