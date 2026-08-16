#pragma once

#include <array>
#include <string>

struct Parameters {
  double threshold = 0.0;
  std::array<std::array<double, 3>, 3> probs{};
  double t1 = 0.0;
  double t2 = 0.0;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
