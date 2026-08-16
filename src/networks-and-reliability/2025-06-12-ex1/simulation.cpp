#include <networks-and-reliability/2025-06-12-ex1/simulation.hpp>

#include <cmath>
#include <random>
#include <vector>

namespace {

struct Vehicle {
  double x = 0.0;
  double y = 0.0;
};

}  // namespace

std::vector<PositionRecord> SimulatePositions(const Parameters& params, urng_t*rng) {
  std::vector<PositionRecord> records;
  if (!rng || params.time_step <= 0.0 || params.num_vehicles <= 0) {
    return records;
  }

  std::uniform_real_distribution<double> pos(-10.0, 10.0);
  std::uniform_real_distribution<double> angle(0.0, 2.0 * M_PI);

  std::vector<Vehicle> vehicles(static_cast<std::size_t>(params.num_vehicles));
  for (auto& vehicle : vehicles) {
    vehicle.x = pos(*rng);
    vehicle.y = pos(*rng);
  }

  int steps = static_cast<int>(params.horizon / params.time_step);
  for (int step = 0; step <= steps; ++step) {
    double time = step * params.time_step;
    for (int i = 0; i < params.num_vehicles; ++i) {
      records.push_back(PositionRecord{
        time,
        i + 1,
        vehicles[static_cast<std::size_t>(i)].x,
        vehicles[static_cast<std::size_t>(i)].y});
    }

    if (step == steps) {
      break;
    }

    for (auto& vehicle : vehicles) {
      double theta = angle(*rng);
      vehicle.x += params.time_step * params.speed * std::sin(theta);
      vehicle.y += params.time_step * params.speed * std::cos(theta);
    }
  }

  return records;
}
