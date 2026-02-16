#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"
#include "../mocc/time.hpp"
#include "parameters.h"
#include "server.h"
#include <vector>

class ECommerceSystem;

class Supplier : public TimerBasedEntity {
 public:
  Supplier(int id, System& system, ECommerceSystem& ecommerce,
           const Parameters& params, urng_t& rng);

  void update(TimerEnded) override;
  void scheduleNextAction(urng_t& rng);

 private:
  int id_;
  ECommerceSystem& ecommerce_;
  Parameters params_;
  urng_t& rng_;
};

#endif
