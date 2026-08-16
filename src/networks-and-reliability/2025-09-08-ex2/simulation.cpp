#include <networks-and-reliability/2025-09-08-ex2/simulation.hpp>

#include <cmath>
#include <random>
#include <vector>

namespace {

struct UAV {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

double DistanceScore(
  double zx,
  double zy,
  double zz,
  const std::vector<UAV>& uavs,
  double L
  ) {
  double score = 0.0;
  double denom = 2.0 * L;
  for (const auto& uav : uavs) {
    double dx = (zx - uav.x) / denom;
    double dy = (zy - uav.y) / denom;
    double dz = (zz - uav.z) / denom;
    score += dx * dx + dy * dy + dz * dz;
  }
  return score;
}

double RunSimulation(const Parameters& params, urng_t*rng) {
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
    std::vector<UAV> next = uavs;
    for (int i = 0; i < params.num_uav; ++i) {
      const UAV& current = uavs[static_cast<std::size_t>(i)];
      double best_score = 0.0;
      bool has_best = false;
      std::vector<UAV> best_positions;

      for (int sx = -1; sx <= 1; sx += 2) {
        for (int sy = -1; sy <= 1; sy += 2) {
          for (int sz = -1; sz <= 1; sz += 2) {
            double zx = current.x + sx * params.V * params.time_step;
            double zy = current.y + sy * params.V * params.time_step;
            double zz = current.z + sz * params.V * params.time_step;
            double score = DistanceScore(zx, zy, zz, uavs, params.L);
            if (!has_best || score < best_score - 1e-12) {
              has_best = true;
              best_score = score;
              best_positions.clear();
              best_positions.push_back(UAV{zx, zy, zz});
            } else if (std::abs(score - best_score) <= 1e-12) {
              best_positions.push_back(UAV{zx, zy, zz});
            }
          }
        }
      }

      if (!best_positions.empty()) {
        std::size_t pick = static_cast<std::size_t>(
          unit(*rng) * best_positions.size());
        if (pick >= best_positions.size()) {
          pick = best_positions.size() - 1;
        }
        next[static_cast<std::size_t>(i)] = best_positions[pick];
      }
    }

    uavs.swap(next);

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

double EstimateCollisionRate(const Parameters& params, urng_t*rng) {
  if (!rng || params.simulations <= 0) {
    return 0.0;
  }

  double total = 0.0;
  for (int i = 0; i < params.simulations; ++i) {
    total += RunSimulation(params, rng);
  }
  return total / params.simulations;
}
