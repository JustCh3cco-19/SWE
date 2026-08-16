#include <networks-and-reliability/2026-01-14-ex1/uav.hpp>

#include <cstddef>

UAV::UAV(int id, const std::array<real_t, 3>& position, real_t time_step)
  : id_(id), position_(position), velocity_{0.0, 0.0, 0.0}, time_step_(time_step) {
}

void UAV::setVelocity(const std::array<real_t, 3>& velocity) {
  velocity_ = velocity;
}

void UAV::update() {
  for (std::size_t k = 0; k < 3; ++k) {
    position_[k] += velocity_[k] * time_step_;
  }
}

const std::array<real_t, 3>& UAV::position() const {
  return position_;
}
