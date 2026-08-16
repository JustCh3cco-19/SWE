#pragma once

// Wraps a value in a distinct, strongly typed alias.
template <typename T>
class Alias {
  public:
  Alias() = default;
  Alias(T value) : value_(value) {
  }

  operator T() const { return value_; }

  private:
  T value_{};
};

#define STRONG_ALIAS(ALIAS, TYPE) \
  class ALIAS : public Alias<TYPE> { \
    public: \
    using Alias<TYPE>::Alias; \
  };
