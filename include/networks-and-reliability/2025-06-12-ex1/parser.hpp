#pragma once

#include <string>

struct Parameters {
  double horizon = 0.0;
  int num_vehicles = 0;
  double speed = 0.0;
  double time_step = 0.0;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
