#include <optimization/2025-03-21-ex2/simulation.hpp>

#include <algorithm>
#include <random>
#include <vector>

namespace {

double Clamp(double value, double min_value, double max_value) {
  return std::min(max_value, std::max(min_value, value));
}

struct Drone {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  bool active = true;
};

int SimulateOperational(const Parameters& params, urng_t*rng) {
  if (!rng || params.horizon <= 0 || params.num_drones <= 0) {
    return 0;
  }

  std::uniform_real_distribution<double> pos_x(params.x1, params.x2);
  std::uniform_real_distribution<double> pos_y(params.y1, params.y2);
  std::uniform_real_distribution<double> pos_z(params.z1, params.z2);
  std::uniform_real_distribution<double> vel(-params.alpha, params.alpha);

  std::vector<Drone> drones(static_cast<std::size_t>(params.num_drones));
  for (auto& drone : drones) {
    drone.x = pos_x(*rng);
    drone.y = pos_y(*rng);
    drone.z = pos_z(*rng);
  }

  double radius_sq = params.radius * params.radius;
  for (int t = 0; t < params.horizon; ++t) {
    for (auto& drone : drones) {
      if (!drone.active) {
        continue;
      }
      drone.x = Clamp(drone.x + vel(*rng), params.x1, params.x2);
      drone.y = Clamp(drone.y + vel(*rng), params.y1, params.y2);
      drone.z = Clamp(drone.z + vel(*rng), params.z1, params.z2);
    }

    std::vector<bool> remove(drones.size(), false);
    for (std::size_t i = 0; i < drones.size(); ++i) {
      if (!drones[i].active) {
        continue;
      }
      for (std::size_t j = i + 1; j < drones.size(); ++j) {
        if (!drones[j].active) {
          continue;
        }
        double dx = drones[i].x - drones[j].x;
        double dy = drones[i].y - drones[j].y;
        double dz = drones[i].z - drones[j].z;
        double dist_sq = dx * dx + dy * dy + dz * dz;
        if (dist_sq <= radius_sq) {
          remove[i] = true;
          remove[j] = true;
        }
      }
    }

    for (std::size_t i = 0; i < drones.size(); ++i) {
      if (remove[i]) {
        drones[i].active = false;
      }
    }
  }

  int active_count = 0;
  for (const auto& drone : drones) {
    if (drone.active) {
      ++active_count;
    }
  }
  return active_count;
}

}  // namespace

OptimizationResult OptimizeAlpha(const Parameters& params, int iterations, urng_t*rng) {
  OptimizationResult result;
  if (!rng || iterations <= 0) {
    return result;
  }

  std::uniform_real_distribution<double> alpha_dist(0.1, 0.5);
  for (int i = 0; i < iterations; ++i) {
    Parameters candidate = params;
    candidate.alpha = alpha_dist(*rng);
    int active = SimulateOperational(candidate, rng);
    double fraction = (candidate.num_drones > 0)
        ? static_cast<double>(active) / candidate.num_drones
        : 0.0;
    if (fraction > result.best_fraction) {
      result.best_fraction = fraction;
      result.best_alpha = candidate.alpha;
    }
  }

  return result;
}
