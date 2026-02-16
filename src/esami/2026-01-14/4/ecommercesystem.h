#ifndef ECOMMERCE_SYSTEM_H
#define ECOMMERCE_SYSTEM_H

#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"
#include "../mocc/time.hpp"
#include "parameters.h"
#include "server.h"
#include <vector>
#include <queue>

struct PendingRequest {
  int customer_id;
  int server_id;
  int product_id;
  int quantity;
  double process_time;  // Tempo a cui processare la richiesta
  
  bool operator>(const PendingRequest& other) const {
    return process_time > other.process_time;  // Min-heap
  }
};

class ECommerceSystem : public SystemObserver {
 public:
  ECommerceSystem(System& system, const Parameters& params, urng_t& rng);

  void submitRequest(int customer_id, int server_id, int product_id, int quantity);
  void submitSupply(int supplier_id, int server_id, int product_id, int quantity);
  void update() override;

  long long getMissedSales() const { return missed_sales_; }

 private:
  Parameters params_;
  std::vector<Server> servers_;
  std::priority_queue<PendingRequest, std::vector<PendingRequest>, std::greater<PendingRequest>> pending_requests_;
  double current_time_;
  long long missed_sales_;
};

#endif
