#ifndef NETWORK_H
#define NETWORK_H

#include "parameters.h"
#include "uav.h"
#include "../mocc/mocc.hpp"
#include "../mocc/system.hpp"
#include "../mocc/time.hpp"

#include <random>
#include <vector>

class Network : public TimerBasedEntity {
 public:
  Network(System& system, const Parameters& params, urng_t& rng);

  void initialize(urng_t& rng, System& system);
  void updateVelocities();
  long long countCollisions() const;
  void update(TimerEnded) override;

  const std::vector<UAV>& getUAVs() const { return uavs_; }

 private:
  Parameters params_;
  std::vector<UAV> uavs_;
  urng_t& rng_;
};

#endif
