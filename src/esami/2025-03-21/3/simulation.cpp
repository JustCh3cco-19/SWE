#include "simulation.hpp"

#include <queue>
#include <random>
#include <vector>

namespace {

int SampleIndex(const std::vector<double>& probs, urng_t* rng) {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double r = dist(*rng);
  double acc = 0.0;
  for (std::size_t i = 0; i < probs.size(); ++i) {
    acc += probs[i];
    if (r <= acc) {
      return static_cast<int>(i);
    }
  }
  return static_cast<int>(probs.size() - 1);
}

}  // namespace

SimulationResult RunSimulation(const Parameters& params, urng_t* rng) {
  SimulationResult result;
  if (!rng || params.horizon <= 0) {
    return result;
  }

  const int n = params.num_servers;
  const int k = params.num_products;

  std::vector<std::queue<int>> customer_queues(static_cast<std::size_t>(n));
  std::vector<std::vector<int>> cache(static_cast<std::size_t>(n), std::vector<int>(k, 0));
  std::vector<std::vector<int>> sold(static_cast<std::size_t>(n), std::vector<int>(k, 0));
  std::vector<int> db(k, 0);
  std::vector<int> update_remaining(static_cast<std::size_t>(n), 0);

  for (int t = 0; t < params.horizon; ++t) {
    for (int i = 0; i < n; ++i) {
      int product = SampleIndex(params.customer_probs, rng);
      if (product > 0) {
        if (customer_queues[static_cast<std::size_t>(i)].size() < 1000) {
          customer_queues[static_cast<std::size_t>(i)].push(product);
        }
      }
    }

    int supply = SampleIndex(params.supplier_probs, rng);
    if (supply > 0 && supply <= k) {
      db[static_cast<std::size_t>(supply - 1)] += 1;
    }

    for (int i = 0; i < n; ++i) {
      std::size_t idx = static_cast<std::size_t>(i);
      if (update_remaining[idx] > 0) {
        update_remaining[idx] -= 1;
        if (update_remaining[idx] == 0) {
          for (int p = 0; p < k; ++p) {
            db[static_cast<std::size_t>(p)] -= sold[idx][static_cast<std::size_t>(p)];
            if (db[static_cast<std::size_t>(p)] < 0) {
              ++result.oversellings;
              db[static_cast<std::size_t>(p)] = 0;
            }
            cache[idx][static_cast<std::size_t>(p)] = db[static_cast<std::size_t>(p)];
            sold[idx][static_cast<std::size_t>(p)] = 0;
          }
        }
        continue;
      }

      if (!customer_queues[idx].empty()) {
        int product = customer_queues[idx].front();
        customer_queues[idx].pop();
        if (product > 0 && product <= k) {
          int p_index = product - 1;
          int available =
              cache[idx][static_cast<std::size_t>(p_index)] -
              sold[idx][static_cast<std::size_t>(p_index)];
          if (available > 0) {
            sold[idx][static_cast<std::size_t>(p_index)] += 1;
          }
        }
        result.transactions += 1;
      }

      std::uniform_real_distribution<double> dist(0.0, 1.0);
      if (dist(*rng) <= params.alpha) {
        update_remaining[idx] = 10;
      }
    }
  }

  return result;
}

double EstimateOversellings(const Parameters& params, int simulations, urng_t* rng) {
  if (!rng || simulations <= 0) {
    return 0.0;
  }

  double total = 0.0;
  for (int i = 0; i < simulations; ++i) {
    SimulationResult result = RunSimulation(params, rng);
    total += result.oversellings;
  }
  return total / simulations;
}
