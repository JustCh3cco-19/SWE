#pragma once

#include <string>
#include <vector>

#include "exam_utils.hpp"

struct Parameters {
  double coverage_limit = 0.0;
  int horizon = 0;
  int num_drones = 0;
  double x1 = 0.0;
  double x2 = 0.0;
  double y1 = 0.0;
  double y2 = 0.0;
  std::vector<mocc_utils::Point> points;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
