#pragma once

#include <string>

struct Parameters {
  double time_step = 0.0;
  double horizon = 0.0;
  int simulations = 0;
  int num_uav = 0;
  double L = 0.0;
  double V = 0.0;
  double A = 0.0;
  double D = 0.0;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
