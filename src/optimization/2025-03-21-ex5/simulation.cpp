#include <optimization/2025-03-21-ex5/simulation.hpp>

#include <queue>
#include <random>
#include <vector>

namespace {

struct Metrics {
  int oversellings = 0;
  int transactions = 0;
};

int SampleIndex(const std::vector<double>& probs, urng_t*rng) {
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

Metrics RunSimulation(const Parameters& params, double alpha, urng_t*rng) {
  const int n = params.num_servers;
  const int k = params.num_products;
  std::vector<std::queue<int> > customer_queues(static_cast<std::size_t>(n));
  std::vector<std::vector<int> > cache(static_cast<std::size_t>(n), std::vector<int>(k, 0));
  std::vector<std::vector<int> > sold(static_cast<std::size_t>(n), std::vector<int>(k, 0));
  std::vector<int> db(k, 0);
  std::vector<int> update_remaining(static_cast<std::size_t>(n), 0);
  Metrics metrics;

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
              ++metrics.oversellings;
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
        metrics.transactions += 1;
      }

      std::uniform_real_distribution<double> dist(0.0, 1.0);
      if (dist(*rng) <= alpha) {
        update_remaining[idx] = 10;
      }
    }
  }

  return metrics;
}

}  // namespace

OptimizationResult OptimizeAlpha(const Parameters& params, int iterations, urng_t*rng) {
  OptimizationResult result;
  if (!rng || iterations <= 0) {
    return result;
  }

  std::uniform_real_distribution<double> alpha_dist(0.0, 1.0);
  for (int i = 0; i < iterations; ++i) {
    double alpha = alpha_dist(*rng);
    Metrics metrics = RunSimulation(params, alpha, rng);
    double denom = params.num_servers * static_cast<double>(params.horizon);
    double w_rate = denom > 0.0 ? metrics.transactions / denom : 0.0;
    double s_rate = denom > 0.0 ? metrics.oversellings / denom : 0.0;
    double j_value = w_rate - s_rate;
    if (i == 0 || j_value > result.j_value) {
      result.alpha = alpha;
      result.w_rate = w_rate;
      result.s_rate = s_rate;
      result.j_value = j_value;
    }
  }

  return result;
}
