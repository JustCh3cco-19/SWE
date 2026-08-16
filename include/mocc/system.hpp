#pragma once

#include <mocc/notifier.hpp>
#include <mocc/observer.hpp>

using SystemObserver = Observer<>;

// Drives entities that observe simulation time.
class System : public Notifier<> {
  public:
  void next() {
    Notifier<>::notify();
  }

};
