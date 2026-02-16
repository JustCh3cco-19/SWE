#pragma once

#include "mocc.hpp"
#include <cmath>

class OnlineDataAnalysis {
  private:
    real_t mean_ = 0, m_2__ = 0;
    size_t number_of_data_points = 0;

  public:
    void insertDataPoint(real_t);

    real_t mean() const;

    real_t stddev() const;
};
