#include "network.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

Network::Network(System& system, const Parameters& params, real_t time_step, urng_t& rng)
    : params_(params),
      rng_(rng),
      timer_(params.T, TimerMode::Repeating, time_step),
      time_step_(time_step) {
  system.addObserver(&timer_);
  timer_.addObserver(this);
}

void Network::initialize(System& system) {
  std::uniform_real_distribution<real_t> dist(-params_.L, params_.L);
  uavs_.clear();
  uavs_.reserve(params_.N);

  for (int i = 0; i < params_.N; ++i) {
    std::array<real_t, 3> pos = {dist(rng_), dist(rng_), dist(rng_)};
    uavs_.emplace_back(i, pos, time_step_);
    system.addObserver(&uavs_.back());
  }
}

void Network::sampleVelocities() {
  std::uniform_real_distribution<real_t> unif(0.0, 1.0);
  for (UAV& uav : uavs_) {
    std::array<real_t, 3> vel;
    const auto& pos = uav.position();
    for (std::size_t k = 0; k < 3; ++k) {
      real_t p = std::exp(-params_.A * (pos[k] + params_.L) / (2.0 * params_.L));
      p = std::clamp(p, 0.0, 1.0);
      vel[k] = (unif(rng_) < p) ? params_.V : -params_.V;
    }
    uav.setVelocity(vel);
  }
}

void Network::update(TimerEnded) {
  sampleVelocities();
}

long long Network::countCollisions() const {
  long long count = 0;
  const real_t d2 = params_.D * params_.D;
  for (std::size_t i = 0; i < uavs_.size(); ++i) {
    const auto& pos_i = uavs_[i].position();
    for (std::size_t j = i + 1; j < uavs_.size(); ++j) {
      const auto& pos_j = uavs_[j].position();
      const real_t dx = pos_i[0] - pos_j[0];
      const real_t dy = pos_i[1] - pos_j[1];
      const real_t dz = pos_i[2] - pos_j[2];
      const real_t dist2 = dx * dx + dy * dy + dz * dz;
      if (dist2 <= d2) {
        ++count;
      }
    }
  }
  return count;
}
