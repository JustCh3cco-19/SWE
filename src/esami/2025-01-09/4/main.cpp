#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "swe_utils.h"

struct Event {
  int time;
  int customer;
};

struct EventCompare {
  bool operator()(const Event& a, const Event& b) const {
    if (a.time != b.time) {
      return a.time > b.time;
    }
    return a.customer > b.customer;
  }
};

int main() {
  std::ifstream input("parameters.txt");
  if (!input) {
    std::cerr << "Cannot open parameters.txt\n";
    return 1;
  }

  int num_customers = 0;
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
    if (tag == "N") {
      row >> num_customers;
    } else if (tag == "Avg") {
      row >> avg;
    } else if (tag == "StdDev") {
      row >> stddev;
    }
  }

  if (num_customers <= 0) {
    std::cerr << "Invalid number of customers\n";
    return 1;
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

  std::priority_queue<Event, std::vector<Event>, EventCompare> queue;
  std::vector<long long> counts(static_cast<size_t>(num_customers), 0);

  for (int i = 0; i < num_customers; ++i) {
    int first_time = SampleInterval();
    if (first_time <= horizon) {
      queue.push(Event{first_time, i});
    }
  }

  long long total_messages = 0;
  while (!queue.empty()) {
    Event current = queue.top();
    if (current.time > horizon) {
      break;
    }
    queue.pop();
    ++counts[static_cast<size_t>(current.customer)];
    ++total_messages;

    int next_time = current.time + SampleInterval();
    if (next_time <= horizon) {
      queue.push(Event{next_time, current.customer});
    }
  }

  std::ofstream output("results.txt");
  if (!output) {
    std::cerr << "Cannot open results.txt\n";
    return 1;
  }

  std::string root_name = swe::RootNameFromCwd();

  output << root_name << "\n";
  for (int i = 0; i < num_customers; ++i) {
    output << (i + 1) << " " << counts[static_cast<size_t>(i)] << "\n";
  }
  output << "M1 " << total_messages << "\n";
  return 0;
}
