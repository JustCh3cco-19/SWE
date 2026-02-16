#ifndef NETWORK_H
#define NETWORK_H

#include "parameters.h"
#include "uav.h"
#include "mocc/mocc.hpp"
#include "mocc/system.hpp"
#include "mocc/time.hpp"

#include <vector>

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
