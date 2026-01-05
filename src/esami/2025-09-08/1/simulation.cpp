#include "simulation.hpp"

#include <cmath>
#include <random>
#include <vector>

namespace {

struct UAV {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

double RunSimulation(const Parameters& params, urng_t* rng) {
  std::uniform_real_distribution<double> pos(-params.L, params.L);
  std::uniform_real_distribution<double> unit(0.0, 1.0);

  std::vector<UAV> uavs(static_cast<std::size_t>(params.num_uav));
  for (auto& uav : uavs) {
    uav.x = pos(*rng);
    uav.y = pos(*rng);
    uav.z = pos(*rng);
  }

  int steps = static_cast<int>(params.horizon / params.time_step);
  double d_sq = params.D * params.D;
  long long collisions = 0;

  for (int step = 0; step < steps; ++step) {
    for (auto& uav : uavs) {
      double p_x = std::exp(-params.A * (uav.x + params.L) / (2.0 * params.L));
      double p_y = std::exp(-params.A * (uav.y + params.L) / (2.0 * params.L));
      double p_z = std::exp(-params.A * (uav.z + params.L) / (2.0 * params.L));
      double vx = (unit(*rng) <= p_x) ? params.V : -params.V;
      double vy = (unit(*rng) <= p_y) ? params.V : -params.V;
      double vz = (unit(*rng) <= p_z) ? params.V : -params.V;
      uav.x += vx * params.time_step;
      uav.y += vy * params.time_step;
      uav.z += vz * params.time_step;
    }

    for (std::size_t i = 0; i < uavs.size(); ++i) {
      for (std::size_t j = i + 1; j < uavs.size(); ++j) {
        double dx = uavs[i].x - uavs[j].x;
        double dy = uavs[i].y - uavs[j].y;
        double dz = uavs[i].z - uavs[j].z;
        if (dx * dx + dy * dy + dz * dz <= d_sq) {
          collisions += 1;
        }
      }
    }
  }

  return collisions / params.horizon;
}

}  // namespace

double EstimateCollisionRate(const Parameters& params, urng_t* rng) {
  if (!rng || params.simulations <= 0) {
    return 0.0;
  }

  double total = 0.0;
  for (int i = 0; i < params.simulations; ++i) {
    total += RunSimulation(params, rng);
  }
  return total / params.simulations;
}
