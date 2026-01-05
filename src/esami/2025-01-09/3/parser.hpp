#pragma once

#include <string>

struct Parameters {
  double avg = 0.0;
  double stddev = 0.0;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
