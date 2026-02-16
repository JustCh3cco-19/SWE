#pragma once

#include "notifier.hpp"
#include "observer.hpp"

using SystemObserver = Observer<>;

class System : public Notifier<> {
  public:
    void next() { Notifier<>::notify(); }
};
