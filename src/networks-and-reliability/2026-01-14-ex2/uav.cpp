#include <networks-and-reliability/2026-01-14-ex2/uav.hpp>
#include <networks-and-reliability/2026-01-14-ex2/network.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <random>

UAV::UAV(int id, const std::array<double, 3>& position, Network*network,
         double V, double L, double time_step, urng_t& rng)
  : id_(id),
  position_(position),
  velocity_{0.0, 0.0, 0.0},
  network_(network),
  V_(V),
  L_(L),
  time_step_(time_step),
  rng_(rng) {
}

void UAV::chooseAndSetVelocity() {
  // Ottiene posizioni di tutti gli altri UAV
  const auto& all_uavs = network_->getUAVs();
  std::vector<std::array<double, 3> > other_positions;
  other_positions.reserve(all_uavs.size() - 1);

  for (const auto& uav : all_uavs) {
    if (&uav != this) {
      other_positions.push_back(uav.position());
    }
  }

  // Prova tutte le 8 combinazioni di velocità
  double best_cost = std::numeric_limits<double>::infinity();
  std::vector<std::array<double, 3> > best_velocities;

  for (int v0 : {-1, 1}) {
    for (int v1 : {-1, 1}) {
      for (int v2 : {-1, 1}) {
        std::array<double, 3> candidate_vel = {
          v0*V_, v1*V_, v2*V_
        };

        // Calcola posizione candidata al tempo t+1
        std::array<double, 3> candidate_pos = {
          position_[0] + candidate_vel[0] * time_step_,
          position_[1] + candidate_vel[1] * time_step_,
          position_[2] + candidate_vel[2] * time_step_
        };

        double cost = computeCost(candidate_pos, other_positions, L_);

        if (cost < best_cost - 1e-9) {
          best_cost = cost;
          best_velocities.clear();
          best_velocities.push_back(candidate_vel);
        } else if (std::abs(cost - best_cost) < 1e-9) {
          best_velocities.push_back(candidate_vel);
        }
      }
    }
  }

  // Sceglie random tra le velocità migliori
  if (!best_velocities.empty()) {
    std::uniform_int_distribution<size_t> dist(0, best_velocities.size() - 1);
    velocity_ = best_velocities[dist(rng_)];
  }
}

void UAV::update() {
  for (std::size_t k = 0; k < 3; ++k) {
    position_[k] += velocity_[k] * time_step_;
  }
}

const std::array<double, 3>& UAV::position() const {
  return position_;
}

void UAV::setPosition(const std::array<double, 3>& pos) {
  position_ = pos;
}

double UAV::computeCost(const std::array<double, 3>& candidate_pos,
                        const std::vector<std::array<double, 3> >& other_positions,
                        double L) const {
  double sum = 0.0;

  for (const auto& other_pos : other_positions) {
    for (std::size_t k = 0; k < 3; ++k) {
      double diff = (candidate_pos[k] - other_pos[k]) / (2.0 * L);
      sum += diff * diff;
    }
  }

  return sum;
}
