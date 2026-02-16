#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"
#include "../mocc/time.hpp"
#include "parameters.h"
#include "network.h"

class Supplier : public TimerBasedEntity {
 public:
  Supplier(int id, System& system, Network& network,
           const Parameters& params, urng_t& rng);

  void update(TimerEnded) override;
  void scheduleNextAction(urng_t& rng);

 private:
  int id_;
  Network& network_;
  Parameters params_;
  urng_t& rng_;
};

#endif
