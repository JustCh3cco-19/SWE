#include "simulation.hpp"

#include <queue>
#include <random>

namespace {

int NextState(const std::array<std::array<double, 3>, 3>& probs, int state, urng_t* rng) {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double r = dist(*rng);
  double acc = 0.0;
  for (int j = 0; j < 3; ++j) {
    acc += probs[static_cast<std::size_t>(state)][static_cast<std::size_t>(j)];
    if (r <= acc) {
      return j;
    }
  }
  return 2;
}

bool RunSimulation(const Parameters& params, int horizon, urng_t* rng) {
  std::queue<int> requests;
  double remaining = 0.0;
  int state = 0;
  bool customer_done = false;
  bool exceeded = false;

  for (int t = 0; t < horizon; ++t) {
    if (!customer_done) {
      int prev_state = state;
      state = NextState(params.probs, state, rng);
      if (state == 1 || state == 2) {
        requests.push(state);
      }
      if (prev_state != 0 && state == 0) {
        customer_done = true;
      }
    }

    if (remaining <= 0.0 && !requests.empty()) {
      int type = requests.front();
      requests.pop();
      remaining = (type == 1) ? params.t1 : params.t2;
    }

    if (remaining > 0.0) {
      remaining -= 1.0;
    }

    if (static_cast<double>(requests.size()) > params.threshold) {
      exceeded = true;
    }

    if (customer_done && requests.empty() && remaining <= 0.0) {
      customer_done = false;
      state = 0;
    }
  }

  return exceeded;
}

}  // namespace

double EstimateProbability(const Parameters& params, int simulations, urng_t* rng) {
  if (!rng || simulations <= 0) {
    return 0.0;
  }

  const int horizon = 10000;
  int success = 0;
  for (int i = 0; i < simulations; ++i) {
    if (RunSimulation(params, horizon, rng)) {
      ++success;
    }
  }
  return static_cast<double>(success) / simulations;
}
