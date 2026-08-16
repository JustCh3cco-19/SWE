#pragma once

#include <string>

struct Parameters {
  int num_customers = 0;
  double avg = 0.0;
  double stddev = 0.0;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
