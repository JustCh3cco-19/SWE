#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX5_NETWORK_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX5_NETWORK_HPP_

#include <ecommerce/2026-01-14-ex5/parameters.hpp>
#include <ecommerce/2026-01-14-ex5/server.hpp>
#include <mocc/mocc.hpp>
#include <mocc/system.hpp>

#include <vector>
#include <queue>

struct PendingRequest {
  int customer_id;
  int server_id;
  int product_id;
  int quantity;
  double process_time;

  bool operator>(const PendingRequest& other) const {
    return process_time > other.process_time;
  }

};

// Coordinates entities and events in the simulation network.
class Network : public SystemObserver {
  public:
  Network(System& system, const Parameters& params, urng_t& rng);

  void submitRequest(int customer_id, int server_id, int product_id, int quantity);
  void submitSupply(int supplier_id, int server_id, int product_id, int quantity);
  void update() override;

  long long missedSales() const {
    return missed_sales_;
  }

  private:
  Parameters params_;
  std::vector<Server> servers_;
  std::priority_queue<PendingRequest, std::vector<PendingRequest>,
                      std::greater<PendingRequest> > pending_requests_;
  double current_time_;
  long long missed_sales_;
};

#endif
