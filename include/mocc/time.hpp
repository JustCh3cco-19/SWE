#pragma once

#include <mocc/alias.hpp>
#include <mocc/mocc.hpp>
#include <mocc/notifier.hpp>
#include <mocc/system.hpp>

STRONG_ALIAS(StopwatchElapsedTime, real_t)

// Emits the elapsed simulation time at every system tick.
class Stopwatch : public SystemObserver,
  public Notifier<StopwatchElapsedTime> {
  public:
  explicit Stopwatch(real_t time_step = 1);

  real_t elapsedTime();
  void reset();
  void update() override;

  private:
  real_t elapsed_time = 0;
  const real_t time_step;
};

STRONG_ALIAS(TimerEnded, real_t)

enum class TimerMode {
  Once,
  Repeating,
};

// Emits a notification when a configured duration has elapsed.
class Timer : public SystemObserver, public Notifier<TimerEnded> {
  public:
  Timer(real_t duration, TimerMode mode, real_t time_step);

  void resetWithDuration(real_t duration);
  void update() override;

  private:
  real_t duration;
  real_t elapsed_time = 0;
  bool is_finished = false;
  const real_t time_step;
  TimerMode mode;
};

// Connects a timer to a simulation system and observes timer events.
class TimerBasedEntity : public Observer<TimerEnded> {
  protected:
  Timer timer;

  public:
  TimerBasedEntity(System& system, real_t duration, TimerMode mode,
                   real_t time_step)
    : timer(duration, mode, time_step) {
    system.addObserver(&timer);
    timer.addObserver(this);
  }

};
