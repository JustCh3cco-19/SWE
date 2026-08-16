#include <optimization/2025-09-08-ex5/simulation.hpp>

#include <queue>
#include <random>
#include <vector>

namespace {

double RunSimulation(
  const Parameters& params,
  double min_supply,
  double max_supply,
  urng_t*rng
  ) {
  std::uniform_real_distribution<double> wait_dist(params.min_wait, params.max_wait);
  std::uniform_real_distribution<double> supply_dist(min_supply, max_supply);
  std::uniform_int_distribution<int> product_dist(1, params.num_products);
  std::uniform_int_distribution<int> server_dist(0, params.num_servers - 1);
  std::uniform_int_distribution<int> stock_dist(0, params.max_items);

  struct Timer {
    double remaining = 0.0;
  };

  std::vector<Timer> customer_timers(static_cast<std::size_t>(params.num_customers));
  std::vector<Timer> supplier_timers(static_cast<std::size_t>(params.num_suppliers));

  for (auto& timer : customer_timers) {
    timer.remaining = wait_dist(*rng);
  }
  for (auto& timer : supplier_timers) {
    timer.remaining = supply_dist(*rng);
  }

  std::vector<std::queue<int> > customer_queues(static_cast<std::size_t>(params.num_servers));
  std::vector<std::queue<int> > supplier_queues(static_cast<std::size_t>(params.num_servers));
  std::vector<std::vector<int> > stock(
    static_cast<std::size_t>(params.num_servers),
    std::vector<int>(params.num_products, 0));

  for (int s = 0; s < params.num_servers; ++s) {
    for (int p = 0; p < params.num_products; ++p) {
      stock[static_cast<std::size_t>(s)][static_cast<std::size_t>(p)] = stock_dist(*rng);
    }
  }

  int steps = static_cast<int>(params.horizon / params.time_step);
  long long missed = 0;

  for (int step = 0; step < steps; ++step) {
    for (auto& timer : customer_timers) {
      timer.remaining -= params.time_step;
      if (timer.remaining <= 0.0) {
        int server = server_dist(*rng);
        int product = product_dist(*rng);
        customer_queues[static_cast<std::size_t>(server)].push(product);
        timer.remaining = wait_dist(*rng);
      }
    }

    for (auto& timer : supplier_timers) {
      timer.remaining -= params.time_step;
      if (timer.remaining <= 0.0) {
        int server = server_dist(*rng);
        int product = product_dist(*rng);
        supplier_queues[static_cast<std::size_t>(server)].push(product);
        timer.remaining = supply_dist(*rng);
      }
    }

    for (int s = 0; s < params.num_servers; ++s) {
      std::size_t idx = static_cast<std::size_t>(s);
      if (!supplier_queues[idx].empty()) {
        int product = supplier_queues[idx].front();
        supplier_queues[idx].pop();
        stock[idx][static_cast<std::size_t>(product - 1)] += 1;
      }
      if (!customer_queues[idx].empty()) {
        int product = customer_queues[idx].front();
        customer_queues[idx].pop();
        std::size_t p_index = static_cast<std::size_t>(product - 1);
        if (stock[idx][p_index] > 0) {
          stock[idx][p_index] -= 1;
        } else {
          missed += 1;
        }
      }
    }
  }

  double total_time = steps * params.time_step;
  if (total_time <= 0.0) {
    return 0.0;
  }
  return missed / total_time;
}

}  // namespace

OptimizationResult OptimizeSupply(const Parameters& params, urng_t*rng) {
  OptimizationResult result;
  if (!rng || params.budget <= 0) {
    return result;
  }

  std::uniform_real_distribution<double> v_dist(1.0, 10.0);
  for (int i = 0; i < params.budget; ++i) {
    double v = v_dist(*rng);
    double q = v + 5.0;
    double total = 0.0;
    for (int sim = 0; sim < params.simulations; ++sim) {
      total += RunSimulation(params, v, q, rng);
    }
    double rate = total / params.simulations;
    double cost = 10.0 * v + 2.0 * rate;
    if (i == 0 || cost < result.best_cost) {
      result.best_cost = cost;
      result.best_rate = rate;
      result.best_v = v;
      result.best_q = q;
    }
  }

  return result;
}
