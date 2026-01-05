#include "simulation.hpp"

#include <random>

double EstimateProbability(const Parameters& params, urng_t* rng) {
  if (!rng || params.simulations <= 0 || params.num_states <= 0) {
    return 0.0;
  }

  std::uniform_real_distribution<double> dist(0.0, 1.0);
  int success = 0;

  for (int sim = 0; sim < params.simulations; ++sim) {
    int state = 0;
    double cost = 0.0;
    int safety = 0;
    while (state != params.num_states - 1) {
      const auto& outs = params.transitions[state];
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
    if (cost <= params.cost_limit) {
      ++success;
    }
  }

  return static_cast<double>(success) / params.simulations;
}
