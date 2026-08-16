#include <optimization/2025-11-03-ex3/simulation.hpp>

#include <random>
#include <vector>

namespace {

double EstimateCostForP(const Parameters& params, double p, urng_t*rng) {
  if (!rng || params.simulations <= 0 || params.num_states <= 0) {
    return 0.0;
  }

  std::vector<std::vector<Transition> > transitions = params.transitions;
  transitions[0].clear();
  transitions[0].push_back(Transition{0, p, params.cost_self});
  transitions[0].push_back(Transition{1, 1.0 - p, params.cost_next});

  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double total = 0.0;

  for (int sim = 0; sim < params.simulations; ++sim) {
    int state = 0;
    double cost = 0.0;
    int safety = 0;
    while (state != params.num_states - 1) {
      const auto& outs = transitions[state];
      if (outs.empty()) {
        break;
      }
      double r = dist(*rng);
      double acc = 0.0;
      int next_state = outs.back().to;
      double step_cost = outs.back().cost;
      for (const auto& t : outs) {
        acc += t.prob;
        if (r <= acc) {
          next_state = t.to;
          step_cost = t.cost;
          break;
        }
      }
      cost += step_cost;
      state = next_state;
      if (++safety > 1000000) {
        break;
      }
    }
    total += cost;
  }

  return total / params.simulations;
}

}  // namespace

OptimizationResult OptimizeP(const Parameters& params, urng_t*rng) {
  OptimizationResult result;
  if (!rng || params.budget <= 0) {
    return result;
  }

  std::uniform_real_distribution<double> dist(0.0, 1.0);
  for (int i = 0; i < params.budget; ++i) {
    double p = dist(*rng);
    double expected_cost = EstimateCostForP(params, p, rng);
    double total = params.k_cost * (1.0 - p) + expected_cost;
    if (i == 0 || total < result.best_total) {
      result.best_total = total;
      result.best_p = p;
      result.best_cost = expected_cost;
    }
  }

  return result;
}
