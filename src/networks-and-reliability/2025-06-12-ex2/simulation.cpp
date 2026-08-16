#include <networks-and-reliability/2025-06-12-ex2/simulation.hpp>

#include <array>
#include <cmath>
#include <random>
#include <vector>

namespace {

struct Vehicle {
  double x = 0.0;
  double y = 0.0;
};

bool IsCollision(const Vehicle& v1, const Vehicle& v2, double radius_sq) {
  double dx = v1.x - v2.x;
  double dy = v1.y - v2.y;
  return (dx * dx + dy * dy) <= radius_sq;
}

double RunSimulation(const Parameters& params, urng_t*rng) {
  std::uniform_real_distribution<double> pos(-10.0, 10.0);
  std::uniform_real_distribution<double> angle(0.0, 2.0 * M_PI);
  std::uniform_real_distribution<double> unit(0.0, 1.0);

  std::vector<Vehicle> vehicles(static_cast<std::size_t>(params.num_vehicles));
  for (auto& vehicle : vehicles) {
    vehicle.x = pos(*rng);
    vehicle.y = pos(*rng);
  }

  int steps = static_cast<int>(params.horizon / params.time_step);
  double radius_sq = params.radius * params.radius;
  double time_since_collision = 0.0;
  double sum_intervals = 0.0;
  int collision_count = 0;

  for (int step = 0; step < steps; ++step) {
    std::array<int, 4> quadrant_counts{0, 0, 0, 0};
    const Vehicle& v1 = vehicles[0];
    for (int i = 1; i < params.num_vehicles; ++i) {
      const Vehicle& v = vehicles[static_cast<std::size_t>(i)];
      double dx = v.x - v1.x;
      double dy = v.y - v1.y;
      if (dx * dx + dy * dy <= radius_sq) {
        if (dx >= 0 && dy >= 0) {
          quadrant_counts[0] += 1;
        }
        if (dx >= 0 && dy <= 0) {
          quadrant_counts[1] += 1;
        }
        if (dx <= 0 && dy <= 0) {
          quadrant_counts[2] += 1;
        }
        if (dx <= 0 && dy >= 0) {
          quadrant_counts[3] += 1;
        }
      }
    }

    int min_count = quadrant_counts[0];
    for (int q = 1; q < 4; ++q) {
      if (quadrant_counts[q] < min_count) {
        min_count = quadrant_counts[q];
      }
    }
    std::vector<int> best_quadrants;
    for (int q = 0; q < 4; ++q) {
      if (quadrant_counts[q] == min_count) {
        best_quadrants.push_back(q);
      }
    }
    int chosen = best_quadrants.empty()
        ? 0
        : best_quadrants[static_cast<std::size_t>(
                           unit(*rng) * best_quadrants.size()) %
                         best_quadrants.size()];
    double start = chosen * (M_PI / 2.0);
    double theta1 = start + unit(*rng) * (M_PI / 2.0);

    vehicles[0].x += params.time_step * params.speed * std::sin(theta1);
    vehicles[0].y += params.time_step * params.speed * std::cos(theta1);

    for (int i = 1; i < params.num_vehicles; ++i) {
      double theta = angle(*rng);
      vehicles[static_cast<std::size_t>(i)].x +=
        params.time_step * params.speed * std::sin(theta);
      vehicles[static_cast<std::size_t>(i)].y +=
        params.time_step * params.speed * std::cos(theta);
    }

    time_since_collision += params.time_step;
    bool collision = false;
    for (int i = 1; i < params.num_vehicles; ++i) {
      if (IsCollision(vehicles[0], vehicles[static_cast<std::size_t>(i)], radius_sq)) {
        collision = true;
        break;
      }
    }
    if (collision) {
      sum_intervals += time_since_collision;
      time_since_collision = 0.0;
      ++collision_count;
    }
  }

  if (collision_count == 0) {
    return steps * params.time_step;
  }
  return sum_intervals / collision_count;
}

}  // namespace

double EstimateCollisionInterval(const Parameters& params, int simulations, urng_t*rng) {
  if (!rng || simulations <= 0) {
    return 0.0;
  }

  double total = 0.0;
  for (int i = 0; i < simulations; ++i) {
    total += RunSimulation(params, rng);
  }
  return total / simulations;
}
