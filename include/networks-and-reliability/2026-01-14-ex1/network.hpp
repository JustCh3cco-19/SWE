#ifndef EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX1_NETWORK_HPP_
#define EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX1_NETWORK_HPP_

#include <networks-and-reliability/2026-01-14-ex1/parameters.hpp>
#include <networks-and-reliability/2026-01-14-ex1/uav.hpp>
#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <mocc/time.hpp>

#include <vector>

// Coordinates entities and events in the simulation network.
class Network : public Observer<TimerEnded> {
  public:
  Network(System& system, const Parameters& params, real_t time_step, urng_t& rng);

  void initialize(System& system);
  void sampleVelocities();
  long long countCollisions() const;
  void update(TimerEnded) override;

  private:
  Parameters params_;
  std::vector<UAV> uavs_;
  urng_t& rng_;
  Timer timer_;
  real_t time_step_;
};

#endif
