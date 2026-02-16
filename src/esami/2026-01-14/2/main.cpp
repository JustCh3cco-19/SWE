#include "network.h"
#include "parameters.h"
#include "../mocc/exam_utils.hpp"
#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"
#include "../mocc/time.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

class CollisionMeasurer : public TimerBasedEntity {
 public:
  CollisionMeasurer(System& system, Network& network, const Parameters& params)
      : TimerBasedEntity(system, params.R, TimerMode::Repeating, params.T),
        network_(network),
        horizon_(params.H),
        measure_interval_(params.R),
        current_time_(0.0) {}

  void update(TimerEnded) override {
    current_time_ += measure_interval_;
    if (current_time_ <= horizon_ + 1e-9) {
      total_collisions_ += network_.countCollisions();
    }
  }

  long long getTotalCollisions() const {
    return total_collisions_;
  }

 private:
  Network& network_;
  double horizon_;
  double measure_interval_;
  double current_time_;
  long long total_collisions_ = 0;
};

int main() {
  Parameters params;
  if (!ReadParameters("parameters.txt", params)) {
    return 1;
  }

  urng_t rng = mocc_utils::MakeRng();
  double sum_rates = 0.0;

  for (int sim = 0; sim < params.M; ++sim) {
    System system;
    
    Network network(system, params, rng);
    network.initialize(rng, system);
    network.updateVelocities();  // Inizializza velocità prima di partire
    
    CollisionMeasurer measurer(system, network, params);

    const int total_steps = static_cast<int>(std::ceil(params.H / params.T));
    for (int step = 0; step < total_steps; ++step) {
      system.next();
    }

    sum_rates += static_cast<double>(measurer.getTotalCollisions()) / params.H;
  }

  const double expected_rate = sum_rates / params.M;

  bool success = mocc_utils::WriteResultsToFile(
      "results.txt",
      [&](std::ostream& out) {
        out << "C " << std::setprecision(10) << expected_rate << "\n";
      });

  if (!success) {
    std::cerr << "Cannot write results.txt\n";
    return 1;
  }

  return 0;
}
