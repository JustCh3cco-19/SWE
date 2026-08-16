#pragma once

#include <string>

struct Parameters {
  double horizon = 0.0;
  int num_products = 0;
  double min_wait = 0.0;
  double max_wait = 0.0;
  double time_step = 0.0;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
