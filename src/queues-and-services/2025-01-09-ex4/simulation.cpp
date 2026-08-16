#include <queues-and-services/2025-01-09-ex4/simulation.hpp>

#include <cmath>
#include <queue>
#include <random>
#include <vector>

namespace {

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

}  // namespace

DispatcherResult SimulateDispatcher(
  int num_customers,
  double avg,
  double stddev,
  int horizon,
  urng_t*rng
  ) {
  DispatcherResult result;
  if (!rng || num_customers <= 0 || horizon <= 0) {
    return result;
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

  std::priority_queue<Event, std::vector<Event>, EventCompare> queue;
  result.counts.assign(static_cast<std::size_t>(num_customers), 0);
  result.total_messages = 0;

  for (int i = 0; i < num_customers; ++i) {
    int first_time = SampleInterval();
    if (first_time <= horizon) {
      queue.push(Event{first_time, i});
    }
  }

  while (!queue.empty()) {
    Event current = queue.top();
    if (current.time > horizon) {
      break;
    }
    queue.pop();
    ++result.counts[static_cast<std::size_t>(current.customer)];
    ++result.total_messages;

    int next_time = current.time + SampleInterval();
    if (next_time <= horizon) {
      queue.push(Event{next_time, current.customer});
    }
  }

  return result;
}
