#pragma once

#include "alias.hpp"
#include "mocc.hpp"
#include "notifier.hpp"
#include "system.hpp"

STRONG_ALIAS(StopwatchElapsedTime, real_t)

class Stopwatch : public SystemObserver, public Notifier<StopwatchElapsedTime> {
  private:
    real_t elapsed_time = 0;
    const real_t time_step;

  public:
    Stopwatch(real_t time_step = 1);

    real_t elapsedTime();

    void reset();

    void update() override;
};

STRONG_ALIAS(TimerEnded, real_t)

enum class TimerMode {
    Once,
    Repeating
};

class Timer : public SystemObserver, public Notifier<TimerEnded> {
  private:
    real_t duration, elapsed_time = 0;
    bool is_finished = false;
    const real_t time_step;
    TimerMode mode;

  public:
    Timer(real_t duration, TimerMode mode, real_t time_step);

    void resetWithDuration(real_t duration);

    void update() override;
};
class TimerBasedEntity : public Observer<TimerEnded> {
  protected:
    Timer timer;

  public:
    TimerBasedEntity(
        System &system,
        real_t duration,
        TimerMode mode,
        real_t time_step
    )
        : timer(duration, mode, time_step) {
        system.addObserver(&timer);
        timer.addObserver(this);
    }
};
