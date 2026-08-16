#include <networks-and-reliability/2026-01-14-ex1/network.hpp>
#include <networks-and-reliability/2026-01-14-ex1/parameters.hpp>
#include <mocc/exam_utils.hpp>
#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>

#include <cmath>
#include <iomanip>
#include <iostream>

// Collects collision measurements at regular intervals.
class CollisionMeasurer : public Observer<TimerEnded> {
  public:
  CollisionMeasurer(System& system, Network*network, real_t interval, real_t time_step)
    : network_(network),
    total_collisions_(0),
    timer_(interval, TimerMode::Repeating, time_step) {
    system.addObserver(&timer_);
    timer_.addObserver(this);
  }

  void update(TimerEnded) override {
    total_collisions_ += network_->countCollisions();
  }

  long long getTotalCollisions() const {
    return total_collisions_;
  }

  private:
  Network*network_;
  long long total_collisions_;
  Timer timer_;
};

int main() {
  Parameters params;
  if (!ReadParameters("parameters.txt", params)) {
    return 1;
  }

  urng_t rng = mocc_utils::MakeRng();
  real_t sum_rates = 0.0;

  const real_t time_step = std::min(params.T, params.R) / 10.0;
  const int steps = static_cast<int>(std::ceil(params.H / time_step));

  for (int sim = 0; sim < params.M; ++sim) {
    System system;
    Network network(system, params, time_step, rng);
    network.initialize(system);
    network.sampleVelocities();

    CollisionMeasurer measurer(system, &network, params.R, time_step);

    for (int step = 0; step < steps; ++step) {
      system.next();
    }

    sum_rates += static_cast<real_t>(measurer.getTotalCollisions()) / params.H;
  }

  const real_t expected_rate = sum_rates / params.M;

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
