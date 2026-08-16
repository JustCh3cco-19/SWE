#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX5_CUSTOMER_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX5_CUSTOMER_HPP_

#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>
#include <ecommerce/2026-01-14-ex5/parameters.hpp>
#include <ecommerce/2026-01-14-ex5/network.hpp>

// Simulates customer actions in the ecommerce system.
class Customer : public TimerBasedEntity {
  public:
  Customer(int id, System& system, Network& network,
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
