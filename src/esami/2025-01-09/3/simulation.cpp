#include "simulation.hpp"

#include <cmath>
#include <random>

Stats SimulateCustomer(double avg, double stddev, int horizon, urng_t* rng) {
  Stats stats;
  if (!rng || horizon <= 0) {
    return stats;
  }

  std::normal_distribution<double> dist(avg, stddev);

  auto SampleInterval = [&]() -> int {
    double sample = dist(*rng);
    int seconds = static_cast<int>(std::ceil(sample));
    if (seconds < 1) {
      seconds = 1;
    }
    return seconds;
  };

  int interval = SampleInterval();
  int remaining = interval;
  int count = 0;
  double mean = 0.0;
  double m2 = 0.0;

  for (int t = 0; t < horizon; ++t) {
    --remaining;
    if (remaining <= 0) {
      ++count;
      double delta = interval - mean;
      mean += delta / count;
      double delta2 = interval - mean;
      m2 += delta * delta2;

      interval = SampleInterval();
      remaining = interval;
    }
  }

  double variance = (count > 0) ? (m2 / count) : 0.0;
  stats.avg = mean;
  stats.stddev = (variance > 0.0) ? std::sqrt(variance) : 0.0;
  return stats;
}
