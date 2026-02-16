#include "network.h"

#include <algorithm>
#include <cmath>
#include <cstddef>

Network::Network(System& system, const Parameters& params, urng_t& rng)
    : TimerBasedEntity(system, params.T, TimerMode::Repeating, params.T),
      params_(params),
      rng_(rng) {}

void Network::initialize(urng_t& rng, System& system) {
  std::uniform_real_distribution<double> dist(-params_.L, params_.L);
  uavs_.clear();
  uavs_.reserve(params_.N);
  
  for (int i = 0; i < params_.N; ++i) {
    std::array<double, 3> pos = {dist(rng), dist(rng), dist(rng)};
    uavs_.emplace_back(i, pos, this, params_.V, params_.L, params_.T, rng_);
    system.addObserver(&uavs_.back());
  }
}

void Network::updateVelocities() {
  // Ogni UAV sceglie la sua velocità ottimale
  for (UAV& uav : uavs_) {
    uav.chooseAndSetVelocity();
  }
}

void Network::update(TimerEnded) {
  // Aggiorna velocità per collision avoidance
  updateVelocities();
  // Le posizioni sono aggiornate automaticamente da UAV::update() via SystemObserver
}

long long Network::countCollisions() const {
  long long count = 0;
  const double d2 = params_.D * params_.D;
  
  for (std::size_t i = 0; i < uavs_.size(); ++i) {
    const auto& pos_i = uavs_[i].position();
    for (std::size_t j = i + 1; j < uavs_.size(); ++j) {
      const auto& pos_j = uavs_[j].position();
      const double dx = pos_i[0] - pos_j[0];
      const double dy = pos_i[1] - pos_j[1];
      const double dz = pos_i[2] - pos_j[2];
      const double dist2 = dx * dx + dy * dy + dz * dz;
      if (dist2 <= d2) {
        ++count;
      }
    }
  }
  
  return count;
}
