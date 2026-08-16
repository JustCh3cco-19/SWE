#pragma once

// Receives notifications carrying values of type T.
template <typename ... T>
class Observer {
  public:
  virtual ~Observer() = default;
  virtual void update(T...) = 0;
};
