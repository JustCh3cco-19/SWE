#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX4_SUPPLIER_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX4_SUPPLIER_HPP_

#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>
#include <ecommerce/2026-01-14-ex4/parameters.hpp>
#include <ecommerce/2026-01-14-ex4/server.hpp>
#include <vector>

class ECommerceSystem;

// Simulates supplier actions in the ecommerce system.
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
