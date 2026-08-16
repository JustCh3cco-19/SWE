#include <optimization/2025-06-12-ex5/simulation.hpp>

#include <queue>
#include <random>
#include <vector>

namespace {

double RunSimulation(const Parameters& params, double prob, urng_t*rng) {
  std::uniform_real_distribution<double> wait_dist(params.min_wait, params.max_wait);
  std::uniform_int_distribution<int> product_dist(1, params.num_products);
  std::uniform_int_distribution<int> server_dist(0, params.num_servers - 1);
  std::uniform_int_distribution<int> stock_dist(1, params.max_items);
  std::uniform_real_distribution<double> unit(0.0, 1.0);

  std::queue<int> dispatcher_queue;
  struct DispatcherTask {
    int product = 0;
    double remaining = 0.0;
  };
  DispatcherTask dispatcher;

  struct ServerTask {
    int product = 0;
    double remaining = 0.0;
  };

  std::vector<std::queue<int> > server_queues(static_cast<std::size_t>(params.num_servers));
  std::vector<ServerTask> servers(static_cast<std::size_t>(params.num_servers));
  std::vector<std::vector<int> > stock(
    static_cast<std::size_t>(params.num_servers),
    std::vector<int>(params.num_products, 0));

  for (int s = 0; s < params.num_servers; ++s) {
    for (int p = 0; p < params.num_products; ++p) {
      stock[static_cast<std::size_t>(s)][static_cast<std::size_t>(p)] = stock_dist(*rng);
    }
  }

  int steps = static_cast<int>(params.horizon / params.time_step);
  double remaining_wait = wait_dist(*rng);
  int fail_count = 0;
  int total_sent = 0;

  for (int step = 0; step < steps; ++step) {
    remaining_wait -= params.time_step;
    if (remaining_wait <= 0.0) {
      int product = product_dist(*rng);
      dispatcher_queue.push(product);
      remaining_wait = wait_dist(*rng);
    }

    if (dispatcher.remaining > 0.0) {
      dispatcher.remaining -= params.time_step;
      if (dispatcher.remaining <= 0.0 && dispatcher.product > 0) {
        int server = server_dist(*rng);
        server_queues[static_cast<std::size_t>(server)].push(dispatcher.product);
        total_sent += 1;
        dispatcher.product = 0;
      }
    }
    if (dispatcher.remaining <= 0.0 && dispatcher.product == 0 &&
        !dispatcher_queue.empty()) {
      dispatcher.product = dispatcher_queue.front();
      dispatcher_queue.pop();
      dispatcher.remaining = params.dispatcher_time;
      if (dispatcher.remaining <= 0.0) {
        int server = server_dist(*rng);
        server_queues[static_cast<std::size_t>(server)].push(dispatcher.product);
        total_sent += 1;
        dispatcher.product = 0;
      }
    }

    for (int s = 0; s < params.num_servers; ++s) {
      std::size_t idx = static_cast<std::size_t>(s);
      if (servers[idx].remaining > 0.0) {
        servers[idx].remaining -= params.time_step;
        if (servers[idx].remaining <= 0.0 && servers[idx].product > 0) {
          int product = servers[idx].product;
          int p_index = product - 1;
          if (stock[idx][static_cast<std::size_t>(p_index)] > 0) {
            stock[idx][static_cast<std::size_t>(p_index)] -= 1;
          } else {
            fail_count += 1;
            if (unit(*rng) <= prob) {
              stock[idx][static_cast<std::size_t>(p_index)] += 10;
            } else {
              int random_server = server_dist(*rng);
              int random_product = product_dist(*rng) - 1;
              stock[static_cast<std::size_t>(random_server)][
                static_cast<std::size_t>(random_product)] += 10;
            }
          }
          servers[idx].product = 0;
        }
      }
      if (servers[idx].remaining <= 0.0 && servers[idx].product == 0 &&
          !server_queues[idx].empty()) {
        servers[idx].product = server_queues[idx].front();
        server_queues[idx].pop();
        servers[idx].remaining = params.server_time;
        if (servers[idx].remaining <= 0.0 && servers[idx].product > 0) {
          int product = servers[idx].product;
          int p_index = product - 1;
          if (stock[idx][static_cast<std::size_t>(p_index)] > 0) {
            stock[idx][static_cast<std::size_t>(p_index)] -= 1;
          } else {
            fail_count += 1;
            if (unit(*rng) <= prob) {
              stock[idx][static_cast<std::size_t>(p_index)] += 10;
            } else {
              int random_server = server_dist(*rng);
              int random_product = product_dist(*rng) - 1;
              stock[static_cast<std::size_t>(random_server)][
                static_cast<std::size_t>(random_product)] += 10;
            }
          }
          servers[idx].product = 0;
          servers[idx].remaining = 0.0;
        }
      }
    }
  }

  if (total_sent == 0) {
    return 0.0;
  }
  return static_cast<double>(fail_count) / total_sent;
}

}  // namespace

OptimizationResult OptimizeP(const Parameters& params, urng_t*rng) {
  OptimizationResult result;
  if (!rng || params.budget <= 0) {
    return result;
  }

  std::uniform_real_distribution<double> prob_dist(0.0, 1.0);
  for (int i = 0; i < params.budget; ++i) {
    double prob = prob_dist(*rng);
    double total = 0.0;
    for (int sim = 0; sim < params.simulations; ++sim) {
      total += RunSimulation(params, prob, rng);
    }
    double avg_q = total / params.simulations;
    if (i == 0 || avg_q < result.best_q) {
      result.best_q = avg_q;
      result.best_p = prob;
    }
  }

  return result;
}
