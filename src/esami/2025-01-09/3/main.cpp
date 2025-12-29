#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "swe_utils.h"

int main() {
  std::ifstream input("parameters.txt");
  if (!input) {
    std::cerr << "Cannot open parameters.txt\n";
    return 1;
  }

  double avg = 0.0;
  double stddev = 0.0;
  std::string line;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "Avg") {
      row >> avg;
    } else if (tag == "StdDev") {
      row >> stddev;
    }
  }

  const int horizon = 1000000;
  std::mt19937 rng = swe::MakeRng();
  std::normal_distribution<double> dist(avg, stddev);

  auto SampleInterval = [&]() -> int {
    double sample = dist(rng);
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
  double estimated_stddev = (variance > 0.0) ? std::sqrt(variance) : 0.0;

  std::ofstream output("results.txt");
  if (!output) {
    std::cerr << "Cannot open results.txt\n";
    return 1;
  }

  std::string root_name = swe::RootNameFromCwd();

  output << root_name << "\n";
  output << "Avg " << mean << "\n";
  output << "StdDev " << estimated_stddev << "\n";
  return 0;
}
