#ifndef EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_NETWORK_HPP_
#define EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_NETWORK_HPP_

#include <networks-and-reliability/2026-01-14-ex2/parameters.hpp>
#include <networks-and-reliability/2026-01-14-ex2/uav.hpp>
#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>

#include <random>
#include <vector>

// Coordinates entities and events in the simulation network.
class Network : public TimerBasedEntity {
  public:
  Network(System& system, const Parameters& params, urng_t& rng);

  void initialize(urng_t& rng, System& system);
  void updateVelocities();
  long long countCollisions() const;
  void update(TimerEnded) override;

  const std::vector<UAV>& getUAVs() const {
    return uavs_;
  }

  private:
  Parameters params_;
  std::vector<UAV> uavs_;
  urng_t& rng_;
};

#endif
