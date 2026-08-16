#ifndef EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_UAV_HPP_
#define EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_UAV_HPP_

#include <mocc/mocc.hpp>
#include <mocc/system.hpp>
#include <array>
#include <vector>

class Network;

// Represents an unmanned aerial vehicle in the simulation.
class UAV : public SystemObserver {
  public:
  UAV(int id, const std::array<double, 3>& position, Network*network,
      double V, double L, double time_step, urng_t& rng);

  void chooseAndSetVelocity();
  void update() override;
  const std::array<double, 3>& position() const;
  void setPosition(const std::array<double, 3>& pos);

  private:
  double computeCost(const std::array<double, 3>& candidate_pos,
                     const std::vector<std::array<double, 3> >& other_positions,
                     double L) const;

  int id_;
  std::array<double, 3> position_;
  std::array<double, 3> velocity_;
  Network*network_;
  double V_;
  double L_;
  double time_step_;
  urng_t& rng_;
};

#endif
