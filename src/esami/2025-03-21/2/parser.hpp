#pragma once

#include <string>

struct Parameters {
  int horizon = 0;
  int num_drones = 0;
  double alpha = 0.0;
  double radius = 0.0;
  double x1 = 0.0;
  double x2 = 0.0;
  double y1 = 0.0;
  double y2 = 0.0;
  double z1 = 0.0;
  double z2 = 0.0;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
