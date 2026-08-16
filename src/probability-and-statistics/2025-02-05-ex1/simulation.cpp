#include <probability-and-statistics/2025-02-05-ex1/simulation.hpp>

#include <algorithm>
#include <random>
#include <vector>

namespace {

double Clamp(double value, double min_value, double max_value) {
  return std::min(max_value, std::max(min_value, value));
}

}  // namespace

std::vector<double> SimulateCoverage(
  const Parameters& params,
  urng_t*rng
  ) {
  std::vector<double> averages(params.points.size(), 0.0);
  if (!rng || params.horizon <= 0 || params.num_drones <= 0) {
    return averages;
  }

  struct Drone {
    double x = 0.0;
    double y = 0.0;
  };

  std::uniform_real_distribution<double> pos_x(params.x1, params.x2);
  std::uniform_real_distribution<double> pos_y(params.y1, params.y2);
  std::uniform_real_distribution<double> vel(-0.5, 0.5);

  std::vector<Drone> drones(static_cast<size_t>(params.num_drones));
  for (auto& drone : drones) {
    drone.x = pos_x(*rng);
    drone.y = pos_y(*rng);
  }

  for (int t = 0; t < params.horizon; ++t) {
    for (std::size_t p = 0; p < params.points.size(); ++p) {
      const mocc_utils::Point& point = params.points[p];
      int count = 0;
      double min_x = point.x - 1.0;
      double max_x = point.x + 1.0;
      double min_y = point.y - 1.0;
      double max_y = point.y + 1.0;
      for (const auto& drone : drones) {
        if (drone.x >= min_x && drone.x <= max_x &&
            drone.y >= min_y && drone.y <= max_y) {
          ++count;
        }
      }
      averages[p] = (averages[p] * t + count) / (t + 1.0);
    }

    for (auto& drone : drones) {
      drone.x = Clamp(drone.x + vel(*rng), params.x1, params.x2);
      drone.y = Clamp(drone.y + vel(*rng), params.y1, params.y2);
    }
  }

  return averages;
}
