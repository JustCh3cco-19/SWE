#ifndef EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX1_UAV_HPP_
#define EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX1_UAV_HPP_

#include <mocc/mocc.hpp>
#include <mocc/system.hpp>

#include <array>

// Represents an unmanned aerial vehicle in the simulation.
class UAV : public SystemObserver {
  public:
  UAV(int id, const std::array<real_t, 3>& position, real_t time_step);
  virtual ~UAV() = default;

  void setVelocity(const std::array<real_t, 3>& velocity);
  const std::array<real_t, 3>& position() const;
  void update() override;

  private:
  int id_;
  std::array<real_t, 3> position_;
  std::array<real_t, 3> velocity_;
  real_t time_step_;
};

#endif
