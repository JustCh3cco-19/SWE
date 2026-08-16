#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX5_SUPPLIER_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX5_SUPPLIER_HPP_

#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>
#include <ecommerce/2026-01-14-ex5/parameters.hpp>
#include <ecommerce/2026-01-14-ex5/network.hpp>

// Simulates supplier actions in the ecommerce system.
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
